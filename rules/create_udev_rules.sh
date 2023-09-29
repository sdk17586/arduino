RULES_DIR="/etc/udev/rules.d"

if [ -f "mcu.rules" ]; then

    sudo cp mcu.rules $RULES_DIR/
    echo "mcu.rules has been copied to $RULES_DIR"
else
    echo "mcu.rules file does not exist in the current directory."
fi
