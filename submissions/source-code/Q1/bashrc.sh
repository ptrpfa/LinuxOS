: 'Add the following code to the end of the .bashrc file'
# Initialise variables
SCRIPT="/linux/CSC1107_assignment/CSC1107_Group_2.sh"
COUNTER_FILE="/home/pi/count.txt"
COUNTER=$(cat $COUNTER_FILE)

# Check if counter value exceeds 3
if [ $COUNTER -le 2 ]; then
    # Run script
    sudo $SCRIPT
    # Increment counter
    ((COUNTER++))
    # Update counter file with updated counter value
    echo $COUNTER > $COUNTER_FILE
fi