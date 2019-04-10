# Trollheaven Disk magazine

The Trollheaven Diskmag is a binary file which runs only under the Fedora 28 operating system. 
It was compiled with the g++ compiler under Linux and encrypted with the GnuPG tool.

decrypt: 

  gpg --passphrase trollheaven --verbose file
  
execute: 

  chmod +x file
  
  ./file
  
output hexdump of the binary file:

  strings file
