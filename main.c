#include <stdio.h>
#include <stdlib.h>  // exit, system
#include <time.h>    // time
#include <termios.h> // changing echo
#include <unistd.h>  // usleep
#include <string.h>
#include <ctype.h> // toupper

void menu_shap(char *menu[], int size_of_menu); // take pointer array and length, make shap of all menu
void menu();                                    // print main menu
void loading(char str1[40], char str2[40]);                     // take a string, make loading line, print the string
void account(char user[30]);                    // take username, access account
void header();                                  // clear screen, print header
void administration(char user[30]);             // take permited username, access administration
void setting(char user[30]);                    // take username, access setting of header and pwd
int pwdCheaker(char *file_name);                // take username, open username.txt and check, if match return 1, else 0
void pinCheaker(char *file_name);               // take username, open usernamePin.txt and check, if match continue, else account(user)
int suretyCheaker();                            // ensure, if yes return 1, else 0
int pinGenerate();                              // generate random 4 digit pin
int num_of_space_after(char *name);             // take pointer, convert string, calculate space before the string according to total character
int num_of_space_before(char *name);            // take pointer, convert string, calculate space after the string according to total character
void fprint_string(char *file_name);            // take filename.txt, open file, read and print the file
void disable_echo_mode();                       // making input invisible
void enable_echo_mode();                        // making input visible
void sub_header(char *menu[30], int option);    // print menu heading and under line
void end_line();
char *generateTime();

FILE *fptr;

const int total_character = 90; // maximun character length
char pwd[12];                   // for pwd from file
char u_pwd[12];                 // for pwd from user
char temp[100];
int size; // the size of all pointer array
double cash;
const double min_cash = 200; // minimun cash that can not be withdraw

void disable_echo_mode()
{
    fflush(stdout);
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);          // Get current terminal attributes
    tty.c_lflag &= ~(ECHO | ICANON);        // Disable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &tty); // Set the modified attributes
}

void enable_echo_mode()
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);          // Get current terminal attributes
    tty.c_lflag |= (ECHO | ICANON);         // Enable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &tty); // Set the modified attributes
}

char *generateTime()
{
    time_t current_time = time(NULL); // generate time
    struct tm *local_time = localtime(&current_time);
    return asctime(local_time);
}

int num_of_space_before(char *name)
{
    return ((total_character - 2 - strlen(name)) / 2) + 1;
}

int num_of_space_after(char *name)
{
    return total_character - num_of_space_before(name) - strlen(name) - 2;
}

int pinGenerate()
{
    time_t current_time = time(NULL);
    return (current_time % 1000 + 1000); // making 4 digit
}

int suretyCheaker() // cheaking yes / no return 0/1
{
    char ch;
    int value;
    printf("Are you sure 'y/n' : ");
    scanf("%c", &ch);
    fflush(stdin);

    if (ch == 'y') // if yes return 1
        value = 1;
    else if (ch == 'n') // if no return 0
        value = 0;
    else
        suretyCheaker();

    return value;
}

int pwdCheaker(char *file_name) // take username, check pwd, return 1 / 0
{
    header();
    char file[30];
    // pointer to string
    strcpy(file, file_name);
    strcat(file, ".txt");    // convert username to filename
    fptr = fopen(file, "r"); // opening file
    strcpy(pwd, "");
    strcpy(u_pwd, "");
    fgets(pwd, sizeof pwd, fptr);
    fclose(fptr);

    for (int i = 1; i < 4; i++)
    {
        printf("Enter password : ");
        disable_echo_mode(); // Disable echo mode to hide input and allow character-by-character reading
        char ch;
        // Read characters one by one, handle backspace, and show '*' for input
        int j = 0;
        while ((ch = getchar()) != 10 && i < 11)
        {
            if (ch == 127)
            {
                if (j > 0)
                {
                    j--;             // Move back in the buffer
                    printf("\b \b"); // Erase '*' from screen by moving cursor back, printing space, then moving cursor back again
                } // clearing buffer
            }
            else
            {
                u_pwd[j++] = ch; // Store the character in the password buffer
                printf("*");     // Display '*'
            }
        }
        u_pwd[j] = '\0';    // Null-terminate the password
        enable_echo_mode(); // Enable echo mode back

        if (strcmp(pwd, u_pwd)) // checking pwd
            printf("\n\n**Incorrect Password.**\nTry again for %d time(s).\n", 3 - i);

        else
        {
            printf("\n\n**Correct Password.**\n");
            fflush(stdout);
            usleep(1000000);
            fflush(stdin);
            strcpy(u_pwd, "");
            strcpy(pwd, "");
            return 1; // if match return 1
            break;
        }
    }
    // when mistake 3rd time come out of loop
    strcpy(u_pwd, "");
    strcpy(pwd, "");
    fflush(stdout);
    usleep(1000000);
    fflush(stdin);
    return 0; // if mismatch return 0
}

void pinCheaker(char *file_name) // take username, check pin
{
    header();
    char file[30], user[30];
    int u_pin = 0, pin = 0;

    strcpy(file, file_name);
    strcpy(user, file_name);
    strcat(file, "Pin.txt"); // convert username to filename
    fptr = fopen(file, "r");
    fscanf(fptr, "%d", &pin);
    fclose(fptr);

    strcpy(u_pwd, "");
    int n = 1;
    for (int i = 1; i < 4; i++)
    {
        printf("Enter PIN : ");
        fflush(stdin);
        disable_echo_mode(); // Disable echo mode to hide input and allow character-by-character reading
        char ch;
        int j = 0;
        // Read characters one by one, handle backspace, and show '*' for input
        while ((ch = getchar()) != 10 && j < 11)
        {
            if (ch == 127)
            {
                if (j > 0)
                {
                    j--;             // Move back in the buffer
                    printf("\b \b"); // Erase '*' from screen by moving cursor back, printing space, then moving cursor back again
                }
            }
            else
            {
                u_pwd[j++] = ch; // Store the character in the password buffer
                printf("*");     // Display '*'
            }
        }
        u_pwd[j] = '\0';    // Null-terminate the password
        enable_echo_mode(); // Enable echo mode back
        sscanf(u_pwd, "%d", &u_pin);

        if (pin != u_pin) // checking pwd
        {
            printf("\n\n**Incorrect PIN.**\n");
            printf("Try again for %d time(s).\n", 3 - i);
        }
        else
        {
            printf("\n\n**Correct PIN.**\n");
            n = 0;
            break;
        }
    }
    strcpy(u_pwd, "");
    if (n)
    {
        printf("\n**Action Failed.**\n");

        end_line();
        account(user); // if mismatch back to account
    }
}

void fprint_string(char *file_name) // take full file name, print string
{
    char file[30];

    strcpy(file, file_name); // converting pointer to string
    fptr = fopen(file, "r");
    strcpy(temp, "");
    do
    {
        fgets(temp, sizeof temp, fptr);
        printf("%s", temp); // printing string
        strcpy(temp, "");
    } while (!feof(fptr));
    fclose(fptr);
}

void menu_shap(char *menu[], int size_of_menu)
{
    strcpy(temp, menu[0]);
    // print space string space
    printf("=%*s%s%*s=\n", num_of_space_before(temp), "", temp, num_of_space_after(temp), "");
    strcpy(temp, "");

    for (int i = 0; i < total_character; i++)
        printf("=");

    for (int i = 1; i < size_of_menu; i++)
    {
        strcpy(temp, menu[i]);
        // print space string space
        printf("\n=%*s%d. %s%*s=\n", num_of_space_before(temp) - 3, "", i, temp, num_of_space_after(temp), "");

        for (int i = 0; i < total_character; i++)
            printf("=");
    }
    printf("\n");
}

void header()
{
    fflush(stdout);
    system("clear");

    for (int i = 0; i < total_character; i++)
        printf("=");
    printf("\n");

    char *bank_info[] = {
        "BankName.txt",
        "BankAddress.txt",
        "BankNumber.txt"};

    for (int i = 0; i < 3; i++)
    {
        fptr = fopen(bank_info[i], "r"); // opening file
        if (fptr == NULL)                // if didn't find
        {
            fclose(fptr);

            fptr = fopen(bank_info[i], "w"); // create
            fprintf(fptr, "Set bank info in administration Default password 111111");
            fclose(fptr);

            fptr = fopen(bank_info[i], "r");
        }
        fgets(temp, sizeof temp, fptr);
        printf("=%*s%s%*s=\n", num_of_space_before(temp), "", temp, num_of_space_after(temp), "");

        strcpy(temp, "");
        fclose(fptr);
    }
    for (int i = 0; i < total_character; i++)
        printf("=");
    printf("\n\n\n");
}

void sub_header(char *menu[30], int option) //
{
    // print space string space
    header();
    printf("=%*s%s%*s=\n", num_of_space_before(menu[option]) - 1, "", menu[option], num_of_space_after(menu[option]) + 1, "");

    for (int i = 0; i < total_character; i++)
        printf("=");
    printf("\n");
}

void loading(char str1[40], char str2[40])
{
    for (int i = 0; i <= 100; i++)
    {
        system("clear");
        printf("\n\n\n\t\t%s : [", str1);
        for (int j = 0; j < i / 4; j++)  // print '=' for 50 times
            printf("=");                 // print '=' for i time
        printf(">");                     // =====(i time)==>
        for (int j = i / 4; j < 25; j++) // print ' ' for 50-(i/2) time
            printf(" ");
        printf("\b] %d%%", i); // last time '>' remove [=========] 100%
        fflush(stdout);
        usleep(20000);
        printf("\r");
    }
    printf("\n\n\t**%s**\n", str2);
    fflush(stdout);
    usleep(3000000);
    fflush(stdin);
    system("clear");
}

void end_line()
{
    for (int i = 0; i < total_character; i++)
        printf("=");
    printf("\nPress enter to continue.");
    getchar();
}

void setting(char user[30]) // set -> bank name, address, number, admin pwd
{
    header();
    char *setting_menu[] = {
        "Setting",
        "Change Bank name",
        "Change Bank address",
        "Change Bank number",
        "Change Admin password",
        "Back"};
    // size of pointer array = size of pointer array / size of pointer
    //   6  =  (6x8 bytes) / 8
    size = sizeof setting_menu / sizeof setting_menu[0];
    menu_shap(setting_menu, size);

    printf("Please enter an option : ");

    int option;
    fflush(stdin);
    scanf("%d", &option);
    fflush(stdin);

    if (option == 1)
    {
        if (pwdCheaker("AdminPassword")) // checking pwd
        {
            header();
            sub_header(setting_menu, option);

            printf("Enter new bank name : ");
            fgets(temp, sizeof temp, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            fflush(stdin);

            if (suretyCheaker()) // ensuring
            {
                fptr = fopen("BankName.txt", "w");
                fprintf(fptr, "%s", temp); // saving in file
                strcpy(temp, "");
                fclose(fptr);

                fptr = fopen("BankNotification.txt", "a"); // print in notification
                fprintf(fptr, "%s has changed bank name, TIME:%s \b", user, generateTime());
                fclose(fptr);

                printf("\n**Successfully Bank name is changed.**\n");
            }
            else
                printf("\n**Bank name is not changed.**\n");

            end_line();
            setting(user);
        }
        else
            setting(user);
    }
    else if (option == 2)
    {
        if (pwdCheaker("AdminPassword")) // checking pwd
        {
            header();
            sub_header(setting_menu, option);

            printf("Enter new bank address : ");
            fgets(temp, sizeof temp, stdin);
            temp[strcspn(temp, "\n")] = '\0'; // converting the last \n into null
            fflush(stdin);

            if (suretyCheaker()) // ensuring
            {
                fptr = fopen("BankAddress.txt", "w");
                fprintf(fptr, "%s", temp); // saving in file
                strcpy(temp, "");
                fclose(fptr);

                fptr = fopen("BankNotification.txt", "a"); // print in notification
                fprintf(fptr, "%s has changed bank address, TIME:%s \b", user, generateTime());
                fclose(fptr);

                printf("\n**Successfully Bank address is changed.**\n");
            }
            else
                printf("\n**Bank address is not changed.**\n");

            end_line();
            setting(user);
        }
        else
            setting(user);
    }
    else if (option == 3)
    {
        if (pwdCheaker("AdminPassword"))
        {
            header();
            sub_header(setting_menu, option);

            printf("Enter new bank number : ");
            fgets(temp, sizeof temp, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            fflush(stdin);

            if (suretyCheaker()) // ensuring
            {
                fptr = fopen("BankNumber.txt", "w");
                fprintf(fptr, "%s", temp); // saving in file
                strcpy(temp, "");
                fclose(fptr);

                fptr = fopen("BankNotification.txt", "a"); // print in notification
                fprintf(fptr, "%s has changed bank number, TIME:%s \b", user, generateTime());
                fclose(fptr);

                printf("\n**Successfully Bank number is changed.**\n");
            }
            else
                printf("\n**Bank number is not changed.**\n");

            end_line();
            setting(user);
        }
        else
            setting(user);
    }
    else if (option == 4)
    {
        if (pwdCheaker("AdminPassword")) // checking pwd
        {
            header();
            sub_header(setting_menu, option);

            for (int i = 2; i >= 0; i--)
            {
                do
                {
                    printf("Password must be 6 character.\n");
                    printf("Enter new admin password : ");
                    strcpy(pwd, "");
                    fgets(pwd, sizeof pwd, stdin);
                    pwd[strcspn(pwd, "\n")] = '\0';
                    fflush(stdin);
                } while (strlen(pwd) != 6); // taking 6(must be) character

                printf("Enter again password : ");
                strcpy(u_pwd, "");
                fgets(u_pwd, sizeof u_pwd, stdin);
                u_pwd[strcspn(u_pwd, "\n")] = '\0';
                fflush(stdin);

                char tempPwd[12];
                fptr = fopen("AdminPassword.txt", "r");
                fscanf(fptr, "%s", tempPwd); // saving pwd
                fclose(fptr);

                if (strcmp(pwd, u_pwd))
                    printf("\n**Password did not match.**\nTry again for %d time(s).\n", i);

                else
                { // if the password is same as previous
                    if (!strcmp(tempPwd, pwd)){
                        printf("\n**Admin password is still same.**\n");
                    }
                    else if(suretyCheaker())
                    {
                        fptr = fopen("AdminPassword.txt", "w");
                        fprintf(fptr, "%s", pwd); // saving pwd
                        fclose(fptr);

                        fptr = fopen("BankNotification.txt", "a"); // print in notification
                        fprintf(fptr, "%s has changed admin password, TIME:%s \b", user, generateTime());
                        fclose(fptr);

                        printf("\n**Successfully admin password is changed.**\n");
                    }
                    else
                        printf("\n**Admin password is not changed.**\n");

                    break;
                }
            }
            strcpy(pwd, "");
            strcpy(u_pwd, "");

            end_line();
            setting(user);
        }
        else
            setting(user);
    }
    else if (option == 5) // back
        administration(user);
    else
        setting(user);
}

void account(char user[30])
{
    header();
    double tempCash;

    strcpy(temp, user);
    strcat(temp, "Info.txt");
    fptr = fopen(temp, "r");
    strcpy(temp, "");
    fgets(temp, sizeof temp, fptr);
    fclose(fptr);

    for (int i = 0; user[i] != '\0'; i++)
        temp[i] = toupper((unsigned char)temp[i]);
    printf("\nWelcome %s\n", &temp[7]);
    strcpy(temp, "");

    char *account_menu[] = {
        "Account Menu",
        "Cash Inquiry",
        "Transection",
        "Cash Withdraw",
        "Cash Deposit",
        "Cash Transfer",
        "Info",
        "Change Password",
        "Delete Account",
        "Back"};
    size = sizeof account_menu / sizeof account_menu[0];
    menu_shap(account_menu, size);

    printf("Please enter an option : ");
    int option;
    fflush(stdin);
    scanf("%d", &option);
    fflush(stdin);

    if (option == 1)
    {
        if (pwdCheaker(user))
        {
            header();
            sub_header(account_menu, option);

            strcpy(temp, user);
            strcat(temp, "Cash.txt");
            fptr = fopen(temp, "r");
            fscanf(fptr, "%lf", &cash);
            printf("Total Cash : %.2lf\n", cash); // showing cash
            strcpy(temp, "");
            fclose(fptr);

            end_line();
            account(user);
        }
        else
            account(user);
    }
    else if (option == 2)
    {
        if (pwdCheaker(user))
        {
            header();
            sub_header(account_menu, option);

            strcpy(temp, user);
            strcat(temp, "Transection.txt");
            fprint_string(temp);
            strcpy(temp, "");

            end_line();
            account(user);
        }
        else
            account(user);
    }
    else if (option == 3)
    {
        if (pwdCheaker(user))
        {
            header();
            sub_header(account_menu, option);

            strcpy(temp, user);
            strcat(temp, "Cash.txt");
            fptr = fopen(temp, "r");
            fscanf(fptr, "%lf", &cash); // read user cash
            fclose(fptr);

            printf("Your total cash : %.2lf\n", cash);
            if (cash <= min_cash)
                printf("\n**As your money is not enough, you can not withdraw it.**\n");

            else
            {
                printf("Remain Cash must be more then %.2lf.\n", min_cash);
                printf("How much money do you want to withdraw : ");
                scanf("%lf", &tempCash);
                fflush(stdin);

                if (tempCash > 0 && cash - tempCash >= min_cash && suretyCheaker())
                {
                    pinCheaker(user);
                    printf("\n**Successfully Cash withdraw.**\n");
                    // user
                    strcpy(temp, user);
                    strcat(temp, "Cash.txt");
                    fptr = fopen(temp, "w");
                    cash = cash - tempCash; // decrease user cash
                    fprintf(fptr, "%.2lf", cash);
                    fclose(fptr);

                    strcpy(temp, user);
                    strcat(temp, "Transection.txt"); // print user transection
                    fptr = fopen(temp, "a");
                    fprintf(fptr, "OUT:%.2lf, CASH:%.2lf, TIME:%s \b", tempCash, cash, generateTime());
                    fclose(fptr);
                    // bank
                    fptr = fopen("BankTransection.txt", "a"); // print bank transection
                    fprintf(fptr, "USER:%s, OUT:%.2lf, TIME:%s \b", user, tempCash, generateTime());
                    fclose(fptr);

                    fptr = fopen("BankCash.txt", "r");
                    fscanf(fptr, "%lf", &cash); // read bank cash
                    fclose(fptr);

                    fptr = fopen("BankCash.txt", "w");
                    fprintf(fptr, "%.2lf", cash - tempCash); // decrease bank cash
                    fclose(fptr);
                }
                else
                    printf("\n**Cash withdraw failed.**\n");
            }
            end_line();
            account(user);
        }
        else
            account(user);
    }
    else if (option == 4)
    {
        if (pwdCheaker(user))
        {
            header();
            sub_header(account_menu, option);

            strcpy(temp, user);
            strcat(temp, "Cash.txt");
            fptr = fopen(temp, "r"); // read cash
            fscanf(fptr, "%lf", &cash);

            printf("How much money do you want to deposit : ");
            scanf("%lf", &tempCash);
            fflush(stdin);
            fclose(fptr);

            if (tempCash > 0 && suretyCheaker())
            {
                pinCheaker(user);
                printf("\n**Successfully Cash deposited.**\n");
                // user
                strcpy(temp, user);
                strcat(temp, "Cash.txt");
                fptr = fopen(temp, "w");
                cash = cash + tempCash;
                fprintf(fptr, "%.2lf", cash); // increase cash
                fclose(fptr);

                strcpy(temp, user);
                strcat(temp, "Transection.txt"); // print user transection
                fptr = fopen(temp, "a");
                fprintf(fptr, "IN:%.2lf, CASH:%.2lf, TIME:%s \b", tempCash, cash, generateTime());
                fclose(fptr);
                // bank
                fptr = fopen("BankTransection.txt", "a"); // print bank transection
                fprintf(fptr, "USER:%s, IN:%.2lf, TIME:%s \b", user, tempCash, generateTime());
                fclose(fptr);

                fptr = fopen("BankCash.txt", "r");
                fscanf(fptr, "%lf", &cash); // read bank cash
                fclose(fptr);

                fptr = fopen("BankCash.txt", "w");
                fprintf(fptr, "%.2lf", cash + tempCash); // increase bank cash
                fclose(fptr);
            }
            else
                printf("\n**Cash Deposit failed.**\n");

            end_line();
            account(user);
        }
        else
            account(user);
    }
    else if (option == 5)
    {
        if (pwdCheaker(user))
        {
            header();
            sub_header(account_menu, option);

            strcpy(temp, user);
            strcat(temp, "Cash.txt");
            fptr = fopen(temp, "r");
            fscanf(fptr, "%lf", &cash); // sender cash
            fclose(fptr);

            printf("Your total cash : %.2lf\n", cash);
            if (cash <= min_cash)
                printf("\n**As your money is not enough, you can not transfer it.**\n");

            else
            {
                char s_user[30];

                printf("To(account no) : ");
                fgets(s_user, sizeof s_user, stdin);
                s_user[strcspn(s_user, "\n")] = '\0';
                strcpy(temp, s_user);
                fflush(stdin);

                if (strcmp(s_user, user))
                {
                    strcat(temp, ".txt");
                    fptr = fopen(temp, "r");
                    if (fptr == NULL)
                    {
                        fclose(fptr);

                        printf("\n**User does not exit.**\n");
                    }
                    else
                    {
                        fclose(fptr);

                        strcpy(temp, s_user);
                        strcat(temp, "Info.txt");
                        fptr = fopen(temp, "r");
                        strcpy(temp, "");
                        fgets(temp, sizeof temp, fptr);
                        fclose(fptr);
                        for (int i = 0; s_user[i] != '\0'; i++)
                            temp[i] = toupper((unsigned char)temp[i]);
                        printf("\n%s\n", temp);
                        strcpy(temp, "");

                        if(!suretyCheaker()){
                            printf("\n**Cash Transfer failed.**\n");
                            end_line();
                            account(user);
                        }

                        printf("Remain Cash must be more then %.2lf.\n", min_cash);
                        printf("How much money do you want to transfer : ");
                        scanf("%lf", &tempCash);
                        fflush(stdin);

                        strcpy(temp, user);
                        strcat(temp, "Cash.txt");
                        fptr = fopen(temp, "r");
                        fscanf(fptr, "%lf", &cash); // read sender cash
                        fclose(fptr);

                        if (tempCash > 0 && cash - tempCash >= min_cash && suretyCheaker())
                        {
                            pinCheaker(user);
                            printf("\n**Successfully Cash Transfered.**\n");
                            // receiver
                            strcpy(temp, s_user);
                            strcat(temp, "Cash.txt");
                            fptr = fopen(temp, "r");
                            fscanf(fptr, "%lf", &cash); // receiver cash
                            fclose(fptr);

                            strcpy(temp, s_user);
                            strcat(temp, "Cash.txt");
                            fptr = fopen(temp, "w");
                            cash = cash + tempCash;
                            fprintf(fptr, "%.2lf", cash); // increase receiver cash
                            fclose(fptr);

                            strcpy(temp, s_user);
                            strcat(temp, "Transection.txt"); // print receiver transection
                            fptr = fopen(temp, "a");
                            fprintf(fptr, "IN:%.2lf, SENDER:%s, CASH:%.2lf, TIME:%s \b", tempCash, user, cash, generateTime());
                            fclose(fptr);
                            // sender
                            strcpy(temp, user);
                            strcat(temp, "Cash.txt");
                            fptr = fopen(temp, "r");
                            fscanf(fptr, "%lf", &cash); // sender cash
                            fclose(fptr);

                            strcpy(temp, user);
                            strcat(temp, "Cash.txt");
                            fptr = fopen(temp, "w");
                            cash = cash - tempCash;
                            fprintf(fptr, "%.2lf", cash); // decrease sender cash
                            fclose(fptr);

                            strcpy(temp, user);
                            strcat(temp, "Transection.txt"); // print sender transection
                            fptr = fopen(temp, "a");
                            fprintf(fptr, "Send:%.2lf, RECEIVER:%s, CASH:%.2lf, TIME:%s \b", tempCash, s_user, cash, generateTime());
                            fclose(fptr);
                            // bank
                            fptr = fopen("BankTransection.txt", "a"); // print bank transection
                            fprintf(fptr, "SENDER:%s, SENT:%.2lf, RECEIVER:%s, TIME:%s \b", user, tempCash, s_user, generateTime());
                            fclose(fptr);
                        }
                        else
                            printf("\n**Cash Transfer failed.**\n");
                    }
                }
                else
                    printf("\n**Cash Transfer failed.**\n");
            }
            end_line();
            account(user);
        }
        else
            account(user);
    }
    else if (option == 6)
    {
        if (pwdCheaker(user))
        {
            header();
            sub_header(account_menu, option);

            strcpy(temp, user);
            strcat(temp, "Info.txt");
            fprint_string(temp);
            strcpy(temp, "");

            end_line();
            account(user);
        }
        else
            account(user);
    }
    else if (option == 7)
    {
        if (pwdCheaker(user))
        {
            header();
            sub_header(account_menu, option);
            strcpy(u_pwd, "");
            strcpy(pwd, "");

            for (int i = 2; i >= 0; i--)
            {
                do
                {
                    printf("Password must be 6 character.\n");
                    printf("Enter new password : ");
                    fgets(pwd, sizeof pwd, stdin);
                    pwd[strcspn(pwd, "\n")] = '\0';
                    fflush(stdin);
                } while (strlen(pwd) != 6);

                printf("Enter again password : ");
                fgets(u_pwd, sizeof u_pwd, stdin);
                u_pwd[strcspn(u_pwd, "\n")] = '\0';
                fflush(stdin);

                char tempPwd[12];
                strcpy(temp, user);
                strcat(temp, ".txt");
                fptr = fopen(temp, "r");
                fscanf(fptr, "%s", tempPwd); // saving pwd
                fclose(fptr);

                if (strcmp(pwd, u_pwd)) // ckecking pwd
                    printf("\n**Password did not match.**\nTry again for %d time(s).\n", i);

                else
                { // if pwd remain same as previous
                    if (!strcmp(pwd, tempPwd))
                    {
                        printf("\n**Password is still same.**\n");
                    }
                    else if(suretyCheaker())
                    {
                        pinCheaker(user);
                        strcpy(temp, user);
                        strcat(temp, ".txt");
                        fptr = fopen(temp, "w");
                        fprintf(fptr, "%s", pwd);
                        fclose(fptr);

                        printf("\n**Successfully password changed.**\n");
                    }
                    else
                        printf("\n**Password is not changed.**\n");

                    break;
                }
            }
            strcpy(temp, "");
            strcpy(u_pwd, "");
            strcpy(pwd, "");

            end_line();
            account(user);
        }
        else
            account(user);
    }
    else if (option == 8)
    {
        header();
        sub_header(account_menu, option);

        strcpy(temp, user);
        strcat(temp, "Cash.txt");
        fptr = fopen(temp, "r");
        fscanf(fptr, "%lf", &cash);
        printf("Your cash : %.2lf\n", cash);
        fclose(fptr);
        if (!suretyCheaker())
        {
            printf("\n**Account is not deleted.**\n");
            end_line();
            account(user);
        }
        if (!pwdCheaker(user))
        {
            account(user);
        }
        pinCheaker(user);

        fptr = fopen("BankNotification.txt", "a");
        fprintf(fptr, "USER:%s Deleted, TIME:%s \b", user, generateTime());
        fclose(fptr);

        strcpy(temp, user);
        strcat(temp, ".txt");
        remove(temp);
        strcpy(temp, user);
        strcat(temp, "Cash.txt");
        remove(temp);
        strcpy(temp, user);
        strcat(temp, "Info.txt");
        remove(temp);
        strcpy(temp, user);
        strcat(temp, "Pin.txt");
        remove(temp);
        strcpy(temp, user);
        strcat(temp, "Transection.txt");
        remove(temp);

        printf("\n\nYour account has been deleted successfully.\n");
        fflush(stdout);
        usleep(2000000);

        menu();
    }
    else if (option == 9)
        menu();
    else
        account(user);
}

void administration(char user[30])
{
    header();
    char *admin_menu[] = {
        "Administration",
        "Transection",
        "Admin log in info",
        "Search account",
        "Cash Inquiry",
        "Notification",
        "Setting",
        "Back"};
    size = sizeof admin_menu / sizeof admin_menu[0];
    menu_shap(admin_menu, size);

    printf("Please enter an option : ");
    int option;
    fflush(stdin);
    scanf("%d", &option);
    fflush(stdin);

    if (option == 1)
    { // transection
        if (pwdCheaker("AdminPassword"))
        {
            header();
            sub_header(admin_menu, option);

            fprint_string("BankTransection.txt");

            end_line();
            administration(user);
        }
        else
            administration(user);
    }
    else if (option == 2)
    { // admin log in info
        if (pwdCheaker("AdminPassword"))
        {
            header();
            sub_header(admin_menu, option);

            fprint_string("AdminLoginInfo.txt");

            end_line();
            administration(user);
        }
        else
            administration(user);
    }
    else if (option == 3)
    { // serch account
        if (pwdCheaker("AdminPassword"))
        {
            char search_name[30];
            header();
            sub_header(admin_menu, option);

            printf("Enter account no : ");
            fgets(search_name, sizeof search_name, stdin);
            search_name[strcspn(search_name, "\n")] = '\0';
            fflush(stdin);

            strcpy(temp, search_name);
            strcat(temp, "Info.txt");
            fptr = fopen(temp, "r");
            if (fptr == NULL)
            {
                printf("\n**User does not exist.**\n");
                fclose(fptr);

                end_line();
                administration(user);
            }
            else
            {
                fclose(fptr);

                printf("\nUser : %s\n", search_name);

                fprint_string(temp);

                end_line();
                administration(user);
            }
            strcpy(temp, "");
        }
        else
            administration(user);
    }
    else if (option == 4) // total cash
    {
        if (pwdCheaker("AdminPassword"))
        {
            header();
            sub_header(admin_menu, option);

            fptr = fopen("BankCash.txt", "r");
            fscanf(fptr, "%lf", &cash);
            printf("Total Cash : %.2lf\n", cash);
            fclose(fptr);

            end_line();
            administration(user);
        }
        else
            administration(user);
    }
    else if (option == 5) // notification
    {
        if (pwdCheaker("AdminPassword"))
        {
            header();
            sub_header(admin_menu, option);

            fprint_string("BankNotification.txt");

            end_line();
            administration(user);
        }
        else
            administration(user);
    }
    else if (option == 6)
        setting(user);
    else if (option == 7) // back
        menu();
    else
        administration(user);
}

void menu()
{
    header();
    char *main_menu[] = {
        "Main menu",
        "Administration",
        "Create Account",
        "Sign in",
        "Exit"};
    // total string = size of the pointer / each string
    size = sizeof main_menu / sizeof main_menu[0];

    char *admin_name[] = {
        "hamim", // add here new admin user
        "dayeen"};
    int admin_name_size = sizeof admin_name / sizeof admin_name[0];

    menu_shap(main_menu, size); // for shap

    printf("Please enter an option : ");
    int option;
    fflush(stdin);
    scanf("%d", &option);
    fflush(stdin);

    if (option == 1)
    { // administration
        header();
        char name[30];
        sub_header(main_menu, option);

        printf("Enter your name : ");
        fgets(name, sizeof name, stdin);
        name[strcspn(name, "\n")] = '\0'; // removing the enter character
        fflush(stdin);

        for (int i = 0; i < size; i++)
        {
            if (!strcmp(admin_name[i], name))
            {
                if (pwdCheaker("AdminPassword")) // cheaking pwd
                {
                    fptr = fopen("AdminLoginInfo.txt", "a");                      // adding loging info
                    fprintf(fptr, "%s log in, TIME:%s \b", name, generateTime()); // name and time
                    fclose(fptr);

                    loading("Loading","Successfully log in.");
                    administration(name);
                }
                else
                {
                    fptr = fopen("AdminLoginInfo.txt", "a"); // adding fail to log in ang go to menu
                    fprintf(fptr, "%s tried but failed, TIME:%s \b", name, generateTime());
                    fclose(fptr);

                    menu();
                }
            }
        }
        printf("\n**You can not enter.**\n");
        fflush(stdout);
        usleep(1000000);
        menu();
    }
    else if (option == 2)
    { // Create account
        sub_header(main_menu,option);
        char u_name[30];

        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        strftime(u_name, sizeof(u_name), "%Y%m%d%H%M%S", tm_info);

        strcpy(temp, u_name);
        strcat(temp, ".txt");
        fptr = fopen(temp, "r"); // cheaking the user exist or not
        if (fptr != NULL)
        {
            fclose(fptr);

            printf("\n**Please try again later.**\n");
            fflush(stdout);
            usleep(1000000);
            menu();
        }
        else if (suretyCheaker())
        {
            fclose(fptr);

            for (int i = 2; i >= 0; i--)
            {
                do
                {
                    printf("\nPassword must be 6 character.\n");
                    printf("Enter password : ");
                    strcpy(u_pwd, "");
                    fgets(u_pwd, sizeof u_pwd, stdin);
                    u_pwd[strcspn(u_pwd, "\n")] = '\0';
                    fflush(stdin);
                } while (strlen(u_pwd) != 6);

                printf("Enter again password : ");
                strcpy(pwd, "");
                fgets(pwd, sizeof pwd, stdin);
                pwd[strcspn(pwd, "\n")] = '\0';
                fflush(stdin);

                if (strcmp(pwd, u_pwd))
                    printf("\n**Password did not match.**\nTry again for %d time(s).\n", i);

                else
                { // for creating account must par minimum cash
                    printf("\n**You have to deposit minimum %.2lf**\n", min_cash);
                    double tempCash;
                    do
                    {
                        printf("How much money do you want to deposit : ");
                        scanf("%lf", &tempCash);
                        fflush(stdin);
                    } while (tempCash < min_cash); // input cash can less then minimun cash

                    printf("\n**Successfully Cash in.**\n");
                    // user
                    strcpy(temp, u_name);
                    strcat(temp, "Cash.txt");
                    fptr = fopen(temp, "w");
                    fprintf(fptr, "%.2lf", tempCash); // printing cash
                    fclose(fptr);

                    strcpy(temp, u_name);
                    strcat(temp, "Transection.txt"); // print user transection
                    fptr = fopen(temp, "w");
                    fprintf(fptr, "IN:%.2lf, CASH:%.2lf, TIME:%s \b", tempCash, tempCash, generateTime());
                    fclose(fptr);
                    // bank
                    fptr = fopen("BankTransection.txt", "a"); // print bank transection
                    fprintf(fptr, "USER:%s, IN:%.2lf, TIME:%s \b", u_name, tempCash, generateTime());
                    fclose(fptr);

                    fptr = fopen("BankCash.txt", "r");
                    fscanf(fptr, "%lf", &cash); // read bank cash
                    fclose(fptr);

                    fptr = fopen("BankCash.txt", "w");
                    fprintf(fptr, "%.2lf", cash + tempCash); // increase bank cash
                    fclose(fptr);

                    fptr = fopen("BankNotification.txt", "a");
                    fprintf(fptr, "NEW USER:%s Created, TIME:%s \b", u_name, generateTime());
                    fclose(fptr);
                    // user
                    strcpy(temp, u_name);
                    strcat(temp, ".txt");
                    fptr = fopen(temp, "w");
                    fprintf(fptr, "%s", u_pwd); // saving pwd
                    fclose(fptr);
                    strcpy(pwd, "");
                    strcpy(u_pwd, "");

                    strcpy(temp, u_name);
                    strcat(temp, "Info.txt"); // info
                    fptr = fopen(temp, "w");
                    strcpy(temp, "");
                    printf("\nEnter your name : ");
                    fgets(temp, sizeof temp, stdin);
                    fflush(stdin);
                    fprintf(fptr, "Name : %s", temp);
                    strcpy(temp, "");
                    printf("Enter your NID : ");
                    fgets(temp, sizeof temp, stdin);
                    fflush(stdin);
                    fprintf(fptr, "NID : %s", temp);
                    strcpy(temp, "");
                    printf("Enter your mobile no : ");
                    fgets(temp, sizeof temp, stdin);
                    fflush(stdin);
                    fprintf(fptr, "Mobile no : %s", temp);
                    strcpy(temp, "");
                    printf("Enter your age : ");
                    fgets(temp, sizeof temp, stdin);
                    fflush(stdin);
                    fprintf(fptr, "Age : %s", temp);
                    strcpy(temp, "");
                    printf("Enter your profession : ");
                    fgets(temp, sizeof temp, stdin);
                    fflush(stdin);
                    fprintf(fptr, "Profession : %s \b", temp);
                    strcpy(temp, "");
                    fclose(fptr);

                    int pin = pinGenerate();
                    printf("\nYour account no : %s", u_name);
                    printf("\nYour PIN :   %d\n\n**Please keep PIN safely.**\n", pin);

                    strcpy(temp, u_name);
                    strcat(temp, "Pin.txt"); // pin
                    fptr = fopen(temp, "w");
                    fprintf(fptr, "%d", pin);
                    fclose(fptr);
                    strcpy(temp, "");

                    printf("\nLog in to access your account.\n");

                    end_line();

                    menu();
                    break;
                }
            }
            fflush(stdout);
            usleep(1000000);
            menu();
        }
        else
        {
            printf("\n**Creating account Failed.**\n");

            end_line();
            menu();
        }
    }
    else if (option == 3)
    { // Account
        header();
        char u_name[30];
        sub_header(main_menu, option);

        printf("Enter account no : ");
        fgets(u_name, sizeof u_name, stdin);
        u_name[strcspn(u_name, "\n")] = '\0';
        printf("%s", temp);
        fflush(stdin);

        strcpy(temp, u_name);
        strcat(temp, ".txt");
        fptr = fopen(temp, "r"); // if username.txt didn't find
        if (fptr == NULL)
        {
            fclose(fptr);

            printf("\n**User does not exist.**\n");
            fflush(stdout);
            usleep(1000000);
            menu();
        }
        else
        {
            fclose(fptr);

            if (pwdCheaker(u_name)) // cheaking pwd
            {
                loading("Loading","Successfully log in.");
                account(u_name);
            }
            else
                menu();
        }
    }
    else if (option == 4)
    {
        printf("\n\n**Successfully EXIT. Thank You.**\n\n");
        fflush(stdout);
        usleep(2000000);
        system("clear");
        exit(0);
    }
    else
        menu();
}

int main(int argc, char const *argv[])
{                                           // opening admin password file as default pwd 111111
    fptr = fopen("AdminPassword.txt", "r"); // read mood
    if (fptr == NULL)                       // if not found
    {
        fclose(fptr);
        fptr = fopen("AdminPassword.txt", "w"); // create file(write mood)
        fprintf(fptr, "111111");
    }
    fclose(fptr);
    // opening admin log in info file
    fptr = fopen("AdminLoginInfo.txt", "r");
    if (fptr == NULL)
    {
        fclose(fptr);
        fptr = fopen("AdminLoginInfo.txt", "w");
    }
    fclose(fptr);
    // opening transection file
    fptr = fopen("BankTransection.txt", "r");
    if (fptr == NULL)
    {
        fclose(fptr);
        fptr = fopen("BankTransection.txt", "w");
    }
    fclose(fptr);
    // opening cash file default cash = 0
    fptr = fopen("BankCash.txt", "r");
    if (fptr == NULL)
    {
        fclose(fptr);
        double bank_cash = 0;
        fptr = fopen("BankCash.txt", "w");
        fprintf(fptr, "%.2lf", bank_cash);
    }
    fclose(fptr);
    // opening bank notification file
    fptr = fopen("BankNotification.txt", "r");
    if (fptr == NULL)
    {
        fclose(fptr);
        fptr = fopen("BankNotification.txt", "w");
    }
    fclose(fptr);

    menu();
    return 0;
}
