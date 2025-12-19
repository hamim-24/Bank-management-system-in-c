# Banking Management System

**[YouTube Video](https://www.youtube.com/watch?v=UjnEz5AukyA)**

A comprehensive terminal-based banking management system written in C. This application provides complete banking functionality including account management, transactions, and administrative controls.

## Features

### User Features
- **Account Creation**: Automatic account number generation with timestamp-based IDs
- **Secure Authentication**: Password protection with hidden input and PIN verification
- **Banking Operations**:
  - Cash deposit and withdrawal
  - Money transfer between accounts
  - Balance inquiry
  - Transaction history
- **Account Management**: Password changes and account deletion
- **User Information**: Personal details storage and viewing

### Administrative Features
- **Admin Panel**: Secure administrative access with separate credentials
- **Transaction Monitoring**: View all bank transactions and user activities
- **User Management**: Search and view user account information
- **Bank Settings**: Configure bank name, address, and contact information
- **Cash Management**: Monitor total bank cash reserves
- **Notification System**: Track all administrative actions and user activities
- **Admin Logging**: Track administrator login attempts and activities

### Security Features
- **Password Protection**: 6-character password requirement with confirmation
- **PIN Verification**: 4-digit PIN for transaction authorization
- **Hidden Input**: Passwords and PINs are masked during entry
- **Access Control**: Separate admin and user authentication systems
- **Attempt Limiting**: Maximum 3 attempts for password/PIN entry

## Prerequisites

- GCC compiler
- Unix-like operating system (Linux, macOS, WSL)
- POSIX-compliant terminal (for password hiding functionality)

## Installation

1. **Clone or download the source code**
2. **Compile the program:**
   ```bash
   gcc -o banking_system main.c
   ```

3. **Run the application:**
   ```bash
   ./banking_system
   ```

## Initial Setup

### Default Configuration
- **Admin Password**: `111111` (change immediately after first login)
- **Admin Users**: `hamim`, `dayeen` (modify in source code if needed)
- **Minimum Balance**: `200.00` (configurable in source code)

### First Run
1. The system will automatically create necessary configuration files
2. Bank information will be set to default values
3. Access administration panel to configure bank details

## Usage

### Main Menu Options

1. **Administration** - Access admin panel (requires admin credentials)
2. **Create Account** - Register a new user account
3. **Sign in** - Access existing user account
4. **Exit** - Close the application

### Creating an Account

1. Select "Create Account" from main menu
2. Confirm account creation
3. Set a 6-character password (with confirmation)
4. Make initial deposit (minimum \$200.00)
5. Enter personal information (name, NID, mobile, age, profession)
6. Receive account number and 4-digit PIN
7. **Important**: Save your account number and PIN securely

### User Account Operations

After logging in with account number and password:

- **Cash Inquiry** - View current balance
- **Transaction** - View transaction history
- **Cash Withdraw** - Withdraw money (PIN required)
- **Cash Deposit** - Deposit money (PIN required)
- **Cash Transfer** - Send money to another account (PIN required)
- **Info** - View personal information
- **Change Password** - Update account password
- **Delete Account** - Permanently remove account

### Administrative Functions

Admin users can access:

- **Transaction** - View all bank transactions
- **Admin log in info** - View administrator login history
- **Search account** - Find and view user account details
- **Cash Inquiry** - View total bank cash reserves
- **Notification** - View system notifications and changes
- **Setting** - Configure bank information and admin password

## File Structure

The system creates and manages multiple files:

```
banking_system/
├── main.c                    # Main source code
├── AdminPassword.txt         # Admin password storage
├── AdminLoginInfo.txt        # Admin login history
├── BankTransection.txt       # All bank transactions
├── BankCash.txt             # Total bank cash
├── BankNotification.txt     # System notifications
├── BankName.txt             # Bank name
├── BankAddress.txt          # Bank address
├── BankNumber.txt           # Bank contact number
└── User Files (per account):
    ├── [AccountNo].txt       # User password
    ├── [AccountNo]Cash.txt   # User balance
    ├── [AccountNo]Info.txt   # User information
    ├── [AccountNo]Pin.txt    # User PIN
    └── [AccountNo]Transection.txt # User transactions
```

## Security Considerations

### Password Requirements
- **User Passwords**: Exactly 6 characters
- **Admin Password**: Exactly 6 characters
- **PIN**: 4-digit number (auto-generated)

### Transaction Security
- PIN verification required for all money transactions
- Minimum balance enforcement (\$200.00)
- Transaction logging with timestamps
- Account verification for transfers

### Data Protection
- Passwords stored in plain text files (consider encryption for production)
- File-based storage (consider database for production)
- Local file system access required

## Customization

### Adding Admin Users
Edit the `admin_name` array in the source code:
```c
char *admin_name[] = {
    "hamim",
    "dayeen",
    "your_admin_name"  // Add new admin users here
};
```

### Changing Minimum Balance
Modify the `min_cash` constant:
```c
const double min_cash = 200; // Change minimum balance here
```

### Adjusting Display Width
Modify the `total_character` constant:
```c
const int total_character = 90; // Change display width
```

## Troubleshooting

### Common Issues

**"User does not exist" error:**
- Verify the account number is correct
- Ensure the account was created successfully

**Password/PIN not working:**
- Check for correct character count (6 for password, 4 for PIN)
- Ensure caps lock is not affecting input
- Remember passwords are case-sensitive

**File permission errors:**
- Ensure write permissions in the program directory
- Check available disk space

**Display formatting issues:**
- Adjust terminal window size
- Modify `total_character` constant if needed

### Recovery Options

**Forgot Admin Password:**
- Delete `AdminPassword.txt` file
- Restart program (will reset to default: 111111)

**Reset Bank Data:**
- Delete all `.txt` files in program directory
- Restart program for fresh installation

## Development Notes

### Code Structure
- **Modular Functions**: Separate functions for each operation
- **File I/O**: Extensive use of file operations for data persistence
- **Terminal Control**: POSIX terminal functions for secure input
- **Menu System**: Hierarchical menu structure with navigation

### Potential Improvements
- Database integration instead of file storage
- Password encryption/hashing
- Network connectivity for multi-user access
- GUI interface development
- Enhanced error handling and validation
- Backup and recovery features

## Contributing

To contribute to this project:
1. Fork the repository
2. Create a feature branch
3. Implement improvements
4. Test thoroughly
5. Submit a pull request

## License

This project is open source. Feel free to modify and distribute according to your needs.

## Acknowledgments

- Built with standard C libraries
- Uses POSIX terminal functions for enhanced security
- Designed for educational and practical banking system understanding
```
```

