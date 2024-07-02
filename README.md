# PasswordManager
Goal:
  create a password manager that works when a usb is connected to a laptop

User Stories:
  Dad wants to look at his bank account but can't remember his password. He wants to plugin a USB and just have it remember passwords for him after answering a simple question that he knows.

  Mom wants to look at their joint insurance account due to a medical complication. She does not know the password, but knows personally relevant information that will allow her access to Dad's information.

Design of program:
  A datastore is on a usb
  The datastore has resting encryption and holds enough information to identify a website, pairs it with a username and password combination
  There is a challenge question to verify the user should have access to the database
  

Questions:
  How will the usb execute the code?
  How to get the url?
  
Outline of program:
  lays dormat until password screen is reached
  decrypts passwrod file
  opens file
  gets url
  matches url to password and username
  asks if password needs to be inputed and which account to use
  inputs password
  encrypts file

Items done:
  Encryption (old code neeed to upload)
  
Items to do:

Current bugs:
