#!/bin/bash
# Script to automate transferring of code to Raspberry PI. Make sure to edit the env file and create a copy to .env 

# ENV file
env_file=".env"

# Check file's existence
if [ ! -f "$env_file" ]; then
  echo ".env file does not exist!"
  exit 1
fi

# Read .env file line by line
while IFS= read -r line || [[ -n "$line" ]]; do
    # Parse lines
    if [[ "$line" == *"PI_ADDR"* ]]; then
        PI_ADDR="${line#*=}"
    elif [[ "$line" == *"PI_USER"* ]]; then
        PI_USER="${line#*=}"
    fi
done < "$env_file"

# Transfer file
scp -r * "$PI_USER@$PI_ADDR:~/linux/CSC1107OS/hashing"