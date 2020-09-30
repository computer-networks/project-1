/*****************************************************************************
 * OpenSSL example single client echo server.                                *
 *                                                                           *
 * By: Athula Balachandran <abalacha@cs.cmu.edu>,                            *
 *     Charles Rang <rang972@gmail.com>,                                     *
 *     Wolf Richter <wolf@cs.cmu.edu>                                        *
 *****************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>

#include <openssl/ssl.h>

#define ECHO_PORT 4949
#define BUF_SIZE 4096

int close_socket(int sock)
{
    if (close(sock))
    {
        fprintf(stderr, "Failed closing socket.\n");
        return 1;
    }
    return 0;
}

int main(char* argv[], int argc)
{

    /************ VARIABLE DECLARATIONS ************/
    SSL_CTX *ssl_context;
    SSL *client_context;
    int sock, client_sock, readret;
    socklen_t cli_size;
    struct sockaddr_in addr, cli_addr;
    char buf[BUF_SIZE];
    /************ END VARIABLE DECLARATIONS ************/

    /************ SSL INIT ************/
    SSL_load_error_strings();
    SSL_library_init();
	
	/* The code originally uses TLSv1_server_method(), but it is marked as
	   deprecated for openssl>=1.1.0, if you want to use the version-specific
	   method, make sure to turn of error and warnings in your Makefile */
    if ((ssl_context = SSL_CTX_new(TLS_server_method())) == NULL)
    {
        fprintf(stderr, "Error creating SSL context.\n");
        return EXIT_FAILURE;
    }

    /* register private key */
    if (SSL_CTX_use_PrivateKey_file(ssl_context, "../private/wolf.key",
                                    SSL_FILETYPE_PEM) == 0)
    {
        SSL_CTX_free(ssl_context);
        fprintf(stderr, "Error associating private key.\n");
        return EXIT_FAILURE;
    }

    /* register public key (certificate) */
    if (SSL_CTX_use_certificate_file(ssl_context, "../certs/wolf.crt",
                                     SSL_FILETYPE_PEM) == 0)
    {
        SSL_CTX_free(ssl_context);
        fprintf(stderr, "Error associating certificate.\n");
        return EXIT_FAILURE;
    }
    /************ END SSL INIT ************/

    /************ SERVER SOCKET SETUP ************/
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        SSL_CTX_free(ssl_context);
        fprintf(stderr, "Failed creating socket.\n");
        return EXIT_FAILURE;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(ECHO_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)))
    {
        close_socket(sock);
        SSL_CTX_free(ssl_context);
        fprintf(stderr, "Failed binding socket.\n");
        return EXIT_FAILURE;
    }

    if (listen(sock, 5))
    {
        close_socket(sock);
        SSL_CTX_free(ssl_context);
        fprintf(stderr, "Error listening on socket.\n");
        return EXIT_FAILURE;
    }
    /************ END SERVER SOCKET SETUP ************/

    /************ SINGLE CLIENT ECHO LOOP ************/
    while (1)
    {
        cli_size = sizeof(cli_addr);
        if ((client_sock = accept(sock, (struct sockaddr *) &cli_addr,
             &cli_size)) == -1)
        {
            close(sock);
            SSL_CTX_free(ssl_context);
            fprintf(stderr, "Error accepting connection.\n");
            return EXIT_FAILURE;
        }

        /************ WRAP SOCKET WITH SSL ************/
        if ((client_context = SSL_new(ssl_context)) == NULL)
        {
            close(sock);
            SSL_CTX_free(ssl_context);
            fprintf(stderr, "Error creating client SSL context.\n");
            return EXIT_FAILURE;
        }

        if (SSL_set_fd(client_context, client_sock) == 0)
        {
            close(sock);
            SSL_free(client_context);
            SSL_CTX_free(ssl_context);
            fprintf(stderr, "Error creating client SSL context.\n");
            return EXIT_FAILURE;
        }  

        if (SSL_accept(client_context) <= 0)
        {
            close(sock);
            SSL_free(client_context);
            SSL_CTX_free(ssl_context);
            fprintf(stderr, "Error accepting (handshake) client SSL context.\n");
            return EXIT_FAILURE;
        }
        /************ END WRAP SOCKET WITH SSL ************/

        readret = 0;

        while((readret = SSL_read(client_context, buf, BUF_SIZE)) > 0)
        {
            if (SSL_write(client_context, buf, readret) != readret)
            {
                SSL_shutdown(client_context);
                SSL_free(client_context);
                close_socket(client_sock);
                close_socket(sock);
                SSL_CTX_free(ssl_context);
                fprintf(stderr, "Error sending to client.\n");
                return EXIT_FAILURE;
            }
            memset(buf, 0, BUF_SIZE);
        } 

        if (readret < 0)
        {
            SSL_shutdown(client_context);
            SSL_free(client_context);
            close_socket(client_sock);
            close_socket(sock);
            SSL_CTX_free(ssl_context);
            fprintf(stderr, "Error reading from client socket.\n");
            return EXIT_FAILURE;
        }

        if (close_socket(client_sock))
        {
            SSL_shutdown(client_context);
            SSL_free(client_context);
            close_socket(sock);
            SSL_CTX_free(ssl_context);
            fprintf(stderr, "Error closing client socket.\n");
            return EXIT_FAILURE;
        }
    }
    /************ END SINGLE CLIENT ECHO LOOP ************/


    SSL_CTX_free(ssl_context);
    close_socket(sock);

    return EXIT_SUCCESS;
}
