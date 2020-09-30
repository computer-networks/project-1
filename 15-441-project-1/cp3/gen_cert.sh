#!/bin/bash

# Required
domain=$1
commonname=$domain

# Change to your company details
country=US
state=PA
locality=Pittsburgh
organization=CMU
organizationalunit=Student
email=staff-441@cs.cmu.edu

# Optional
password=dummypassword

if [ -z "$domain" ]
then
    echo "domain not specified."
    echo "use localhost instead."
    domain=localhost
fi

echo "Generating private key for $domain"

# create RNG file
openssl rand -writerand /root/.rnd

# Generate a 2048-bit key
openssl genrsa -des3 -out $domain.key -passout pass:$password 2048

#Remove passphrase from the key. Comment the line out to keep the passphrase
echo "Removing passphrase from key"
openssl rsa -in $domain.key -out $domain.key -passin pass:$password

# Create the request
echo "Creating CSR"
openssl req -new -key $domain.key -out $domain.csr -passin pass:$password \
    -subj "/C=$country/ST=$state/L=$locality/O=$organization/OU=$organizationalunit/CN=$domain/emailAddress=$email"

#Create the cert
echo "Creating the CRT"
openssl x509 -req -days 365 -in $domain.csr -signkey $domain.key -out $domain.crt 

rm $domain.csr
