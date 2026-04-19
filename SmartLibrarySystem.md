//old version
// SmartLibrarySystem.java
import java.util.*;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;
import java.io.*;
public class SmartLibrarySystem {
    private static final String DEFAULT_ADMIN_ID = "UID8888";
    private static final String DEFAULT_FACULTY_ID = "UID5088";
    private static final String DEFAULT_STUDENT_ID = "UID3001";
    private static final String DEFAULT_PUBLIC_ID = "UID0001";
    private static final String DEFAULT_PUBLIC_FINE_ID = "UID0002";
    private static final String DEFAULT_ADMIN_PASSWORD = "admin123";
    private static final String DEFAULT_FACULTY_PASSWORD = "faculty123";
    private static final String DEFAULT_STUDENT_PASSWORD = "student123";
    private static final String DEFAULT_PUBLIC_PASSWORD = "abc123";
    private static final String DEFAULT_PUBLIC_FINE_PASSWORD = "sudo123";

    private static Library library = new Library();
    private static Scanner scanner = new Scanner(System.in);
    private static User currentUser = null;
    private static DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
    public static void main(String[] args) {
        loadData();
       
        while (true) {
            if (currentUser == null) {
                showMainMenu();
            } else {
                showUserMenu();
            }
        }
    }
    private static void showMainMenu() {
        printDefaultUserHint();
        System.out.println("\n========================================");
        System.out.println(" SMART LIBRARY MANAGEMENT SYSTEM");
        System.out.println("========================================");
        System.out.println("1. Login");
        System.out.println("2. Register");
        System.out.println("3. Exit");
        while (true) {
            System.out.print("Choose option: ");
           
            int choice = getIntInput();
           
            switch (choice) {
                case 1:
                    login();
                    return;
                case 2:
                    register();
                    return;
                case 3:
                    System.out.println("Thank you for using the system!");
                    saveData();
                    System.exit(0);
                default:
                    System.out.println("Invalid option!!! Please try again.");
            }
        }
    }
    private static void showUserMenu() {
        System.out.println("\n========================================");
        System.out.println(" Welcome, " + currentUser.getName());
        System.out.println(" User Type: " + currentUser.getUserType());
        System.out.println("========================================");
        System.out.println("1. Search Resources");
        System.out.println("2. Borrow Resource");
        System.out.println("3. Return Resource");
        System.out.println("4. View My Borrowed Items");
        System.out.println("5. Reserve Resource");
        System.out.println("6. Pay Fines");
        System.out.println("7. View My Fines");
        System.out.println("8. Logout");
       
        if (currentUser instanceof Librarian) {
            System.out.println("\n--- LIBRARIAN MENU ---");
            System.out.println("9. Add New Resource");
            System.out.println("10. Update Resource");
            System.out.println("11. Remove Resource");
            System.out.println("12. View All Resources");
            System.out.println("13. View All Users");
            System.out.println("14. Update User");
            System.out.println("15. Delete User");
            System.out.println("16. Generate Reports");
            System.out.println("17. Process Fine Payments");
        }
       
        while (true) {
            System.out.print("Choose option: ");
           
            int choice = getIntInput();
           
            switch (choice) {
                case 1: searchResources(); return;
                case 2: borrowResource(); return;
                case 3: returnResource(); return;
                case 4: viewBorrowedItems(); return;
                case 5: reserveResource(); return;
                case 6: payFines(); return;
                case 7: viewMyFines(); return;
                case 8:
                    currentUser = null;
                    System.out.println("Logged out successfully!");
                    return;
                default:
                    if (currentUser instanceof Librarian) {
                        switch (choice) {
                            case 9: addResource(); return;
                            case 10: updateResource(); return;
                            case 11: removeResource(); return;
                            case 12: viewAllResources(); return;
                            case 13: viewAllUsers(); return;
                            case 14: updateUser(); return;
                            case 15: deleteUser(); return;
                            case 16: generateReports(); return;
                            case 17: processFinePayments(); return;
                            default: System.out.println("Invalid option! Please try again.");
                        }
                    } else {
                        System.out.println("Invalid option! Please try again.");
                    }
            }
        }
    }
    private static void login() {
        System.out.print("Enter User ID: ");
        String userId = scanner.nextLine();
        System.out.print("Enter Password: ");
        String password = scanner.nextLine();
       
        User user = library.authenticateUser(userId, password);
        if (user != null) {
            currentUser = user;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials!");
        }
    }
    private static void register() {
        System.out.println("\n--- User Registration ---");
        System.out.print("Enter Name: ");
        String name = scanner.nextLine();
        System.out.print("Enter Email: ");
        String email = scanner.nextLine();
        System.out.print("Enter Phone: ");
        String phone = scanner.nextLine();
        System.out.print("Enter Address: ");
        String address = scanner.nextLine();
        System.out.print("Create Password: ");
        String password = scanner.nextLine();
       
        System.out.println("User Type:");
        System.out.println("1. Student");
        System.out.println("2. Faculty");
        System.out.println("3. Public Member");
        System.out.println("4. Librarian");
        System.out.print("Choose: ");
        int type = getIntInput();
       
        int borrowLimit = 3;
        int loanDuration = 7;
        String userType = "Student";
       
        switch (type) {
            case 1:
                userType = "Student";
                borrowLimit = 3;
                loanDuration = 7;
                break;
            case 2:
                userType = "Faculty";
                borrowLimit = 10;
                loanDuration = 7;
                break;
            case 3:
                userType = "Public Member";
                borrowLimit = 2;
                loanDuration = 7;
                break;
            case 4:
                Librarian librarian = new Librarian(name, email, phone, address, password);
                library.addUser(librarian);
                System.out.println("Librarian registration successful! Your User ID is: " + librarian.getUserId());
                return;
            default:
                System.out.println("Invalid type, setting as Student");
        }
       
        User user = new User(name, email, phone, address, password, userType, borrowLimit, loanDuration);
        library.addUser(user);
        System.out.println("Registration successful! Your User ID is: " + user.getUserId());
    }
    private static void searchResources() {
        System.out.println("\n--- Search Resources ---");
        System.out.print("Enter search term: ");
        String term = scanner.nextLine();
       
        List<Resource> results = library.searchResources(term);
       
        if (results.isEmpty()) {
            System.out.println("No resources found.");
        } else {
            System.out.println("\n--- Results ---");
            displayResourceTable(results);
        }
    }
    private static void borrowResource() {
        System.out.println("\n--- Borrow Resource ---");
        System.out.println("Available Resources:");
        displayResourceTable(library.getAllResources());
        System.out.print("Enter Resource ID to borrow: ");
        String resourceId = scanner.nextLine();
       
        try {
            Transaction transaction = library.borrowResource(currentUser, resourceId);
            if (transaction != null) {
                System.out.println("Resource borrowed successfully!");
                System.out.println("Due Date: " + transaction.getDueDate().format(dateFormatter));
            }
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
    
    private static void displayResourceTable(List<Resource> resources) {
        if (resources.isEmpty()) {
            System.out.println("No resources to display.");
            return;
        }
        
        System.out.printf("%-12s %-12s %-22s %-15s %-6s %-7s %-16s %-18s %-18s %-10s\n",
                         "Type", "Res ID", "Title", "Author", "Year", "Pages", "ISBN", "Genre", "Publisher", "Status");
        System.out.println("=".repeat(160));
        
        for (Resource r : resources) {
            String type = r.getResourceType();
            if (type.length() > 10) type = type.substring(0, 7) + "...";
            String resourceId = r.getResourceId();
            if (resourceId.length() > 10) resourceId = resourceId.substring(0, 7) + "...";
            String title = r.getTitle();
            if (title.length() > 20) title = title.substring(0, 17) + "...";
            String author = r.getAuthor();
            if (author.length() > 13) author = author.substring(0, 10) + "...";
            String year = String.valueOf(r.getYear());
            String pages = "";
            if (r instanceof Book) {
                pages = String.valueOf(((Book) r).getPages());
            }
            if (pages.length() > 7) pages = pages.substring(0, 4) + "...";
            String isbn = r.getIsbn();
            if (isbn.length() > 14) isbn = isbn.substring(0, 11) + "...";
            String genre = r.getGenre();
            if (genre.length() > 16) genre = genre.substring(0, 13) + "...";
            String publisher = r.getPublisher();
            if (publisher.length() > 16) publisher = publisher.substring(0, 13) + "...";
            String status = r.isAvailable() ? "Available" : "On Loan";
            if (status.length() > 10) status = status.substring(0, 7) + "...";
            
            System.out.printf("%-12s %-12s %-22s %-15s %-6s %-7s %-16s %-18s %-18s %-10s\n",
                             type, resourceId, title, author, year, pages, isbn, genre, publisher, status);
        }
        System.out.println();
    }
    private static void returnResource() {
        System.out.println("\n--- Return Resource ---");
        System.out.println("All Available Resources:");
        System.out.printf("%-15s %-40s %-15s\n", "Resource ID", "Title", "Status");
        System.out.println("--------------------------------------------------------------------------------");
        for (Resource r : library.getAllResources()) {
            System.out.printf("%-15s %-40s %-15s\n",
                              r.getResourceId(), r.getTitle(), r.isAvailable() ? "Available" : "On Loan");
        }
        System.out.println();
       
        List<Transaction> borrowedItems = library.getUserBorrowedItems(currentUser.getUserId());
        List<Transaction> unreturned = new ArrayList<>();
        for (Transaction t : borrowedItems) {
            if (!t.isReturned()) {
                unreturned.add(t);
            }
        }
       
        if (unreturned.isEmpty()) {
            System.out.println("You have no borrowed items to return!");
            return;
        }
       
        System.out.println("Your Borrowed Items:");
        System.out.printf("%-15s %-40s %-15s\n", "Resource ID", "Title", "Due Date");
        System.out.println("--------------------------------------------------------------------------------");
        for (Transaction t : unreturned) {
            Resource r = library.getResource(t.getResourceId());
            if (r != null) {
                System.out.printf("%-15s %-40s %-15s\n",
                                  t.getResourceId(), r.getTitle(), t.getDueDate().toString());
            }
        }
        System.out.println();
       
        System.out.print("Enter Resource ID to return: ");
        String resourceId = scanner.nextLine();
       
        try {
            Transaction transaction = library.returnResource(currentUser, resourceId);
            if (transaction != null) {
                System.out.println("Resource returned successfully!");
                if (transaction.getFineAmount() > 0) {
                    System.out.println("Late return! Fine amount: RM " + transaction.getFineAmount());
                }
            }
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
    private static void viewBorrowedItems() {
        List<Transaction> borrowed = library.getUserBorrowedItems(currentUser.getUserId());
       
        List<Transaction> unreturned = new ArrayList<>();
        for (Transaction t : borrowed) {
            if (!t.isReturned()) {
                unreturned.add(t);
            }
        }
       
        if (unreturned.isEmpty()) {
            System.out.println("No borrowed items.");
        } else {
            System.out.println("\n--- Borrowed Items ---");
            System.out.printf("%-15s %-30s %-12s %-12s %-12s %-15s\n",
                              "Resource ID", "Title", "Borrow Date", "Due Date", "Days Left", "Status");
            System.out.println("-----------------------------------------------------------------------------------------------------------");
           
            for (Transaction t : unreturned) {
                Resource r = library.getResource(t.getResourceId());
                if (r != null) {
                    long daysLeft = ChronoUnit.DAYS.between(LocalDate.now(), t.getDueDate());
                    String status = daysLeft < 0 ? "OVERDUE" : "ON LOAN";
                    String title = r.getTitle();
                    if (title.length() > 28) title = title.substring(0, 25) + "...";
                   
                    System.out.printf("%-15s %-30s %-12s %-12s %-12d %-15s\n",
                                      t.getResourceId(), title, t.getBorrowDate().toString(),
                                      t.getDueDate().toString(), daysLeft, status);
                }
            }
        }
    }
    private static void reserveResource() {
        System.out.println("\n--- Reserve Resource ---");
       
        List<Resource> onLoan = new ArrayList<>();
        List<Resource> available = new ArrayList<>();
       
        for (Resource r : library.getAllResources()) {
            if (!r.isAvailable()) {
                onLoan.add(r);
            } else {
                available.add(r);
            }
        }
       
        System.out.println("Available Resources for Reserving (On Loan):");
        System.out.printf("%-15s %-40s %-20s\n", "Resource ID", "Title", "Status");
        System.out.println("--------------------------------------------------------------------------------");
       
        if (onLoan.isEmpty()) {
            System.out.println("No resources on loan available for reserving.");
        } else {
            for (Resource r : onLoan) {
                System.out.printf("%-15s %-40s %-20s\n",
                                  r.getResourceId(), r.getTitle(), "On Loan - Can Reserve");
            }
        }
       
        System.out.println("\n\nNo Available Resources for Reserving (Available Now):");
        System.out.printf("%-15s %-40s %-20s\n", "Resource ID", "Title", "Status");
        System.out.println("--------------------------------------------------------------------------------");
       
        if (available.isEmpty()) {
            System.out.println("No available resources.");
        } else {
            for (Resource r : available) {
                System.out.printf("%-15s %-40s %-20s\n",
                                  r.getResourceId(), r.getTitle(), "Available Now");
            }
        }
       
        System.out.println();
        System.out.print("Enter Resource ID to reserve: ");
        String resourceId = scanner.nextLine();
       
        boolean success = library.reserveResource(currentUser, resourceId);
        if (success) {
            System.out.println("Resource reserved successfully!");
        } else {
            System.out.println("Failed to reserve resource.");
        }
    }
    
    private static void payFines() {
        List<Fine> fines = library.getUserFines(currentUser.getUserId());
        double total = 0;
       
        if (fines.isEmpty()) {
            System.out.println("You have no fines.");
            return;
        }
       
        System.out.println("\n--- Your Fines ---");
        for (Fine f : fines) {
            if (!f.isPaid()) {
                System.out.println("Fine ID: " + f.getFineId() + " | Amount: RM " + f.getAmount());
                total += f.getAmount();
            }
        }
       
        System.out.println("Total unpaid: RM " + total);
        while (true) {
            System.out.print("Pay all fines? (y/n): ");
            String confirm = scanner.nextLine();
            
            if (confirm.equalsIgnoreCase("y")) {
                library.payFines(currentUser.getUserId());
                System.out.println("Your fine payment was successful.");
                break;
            } else if (confirm.equalsIgnoreCase("n")) {
                System.out.println("You have successfully cancelled all payments.");
                break;
            } else {
                System.out.println("Invalid input. Please enter 'y' or 'n'.");
            }
        }
    }
    private static void viewMyFines() {
        List<Fine> fines = library.getUserFines(currentUser.getUserId());
       
        if (fines.isEmpty()) {
            System.out.println("You have no fines.");
        } else {
            System.out.println("\n--- Fine History ---");
            for (Fine f : fines) {
                System.out.println(f);
            }
        }
    }
    // ==================== USER CRUD OPERATIONS ====================
   
    private static void updateUser() {
        List<User> users = library.getAllUsers();
        if (users.isEmpty()) {
            System.out.println("No users available to update.");
            return;
        }
        
        System.out.println("\n--- Available User ---");
        System.out.printf("%-4s %-20s %-13s %-12s %-15s %-28s %-15s\n",
                          "No.", "Name", "User Type", "ID", "Password", "Email", "Phone");
        System.out.println("---- -------------------- ------------- ------------ --------------- ---------------------------- ---------------");
        int count = 1;
        for (User user : users) {
            String displayType = user.getUserType().equals("Librarian") ? "Admin" : 
                                (user.getUserType().equals("Public Member") ? "Public" : user.getUserType());
            String maskedPassword = maskPassword(user.getPassword());
            String name = user.getName();
            if (name.length() > 20) {
                name = name.substring(0, 17) + "...";
            }
            String email = user.getEmail();
            if (email.length() > 28) {
                email = email.substring(0, 25) + "...";
            }
            System.out.printf("%-4d %-20s %-13s %-12s %-15s %-28s %-15s\n",
                              count, name, displayType, user.getUserId(), maskedPassword, email, user.getPhone());
            count++;
        }
        
        System.out.print("\nEnter User ID to update: ");
        String userId = scanner.nextLine();
       
        User user = library.getUser(userId);
        if (user == null) {
            System.out.println("User not found!");
            return;
        }
       
        System.out.println("\n--- Updating User: " + user.getName() + " ---");
        System.out.println("1. Update Name");
        System.out.println("2. Update Email");
        System.out.println("3. Update Phone");
        System.out.println("4. Update Password");
        System.out.println("5. Cancel");
        System.out.print("Choose: ");
       
        int choice = getIntInput();
       
        switch (choice) {
            case 1:
                System.out.print("Enter new name: ");
                user.setName(scanner.nextLine());
                System.out.println("Name updated successfully!");
                break;
            case 2:
                System.out.print("Enter new email: ");
                user.setEmail(scanner.nextLine());
                System.out.println("Email updated successfully!");
                break;
            case 3:
                System.out.print("Enter new phone: ");
                user.setPhone(scanner.nextLine());
                System.out.println("Phone updated successfully!");
                break;
            case 4:
                System.out.print("Enter new password: ");
                user.setPassword(scanner.nextLine());
                System.out.println("Password updated successfully!");
                break;
            default:
                System.out.println("Update cancelled.");
        }
    }
   
    private static void deleteUser() {
        System.out.print("Enter User ID to delete: ");
        String userId = scanner.nextLine();
       
        User user = library.getUser(userId);
        if (user == null) {
            System.out.println("User not found!");
            return;
        }
       
        System.out.println("Are you sure you want to delete user: " + user.getName() + "? (y/n)");
        String confirm = scanner.nextLine();
       
        if (confirm.equalsIgnoreCase("y")) {
            List<Transaction> borrowed = library.getUserBorrowedItems(userId);
            boolean hasUnreturned = false;
            for (Transaction t : borrowed) {
                if (!t.isReturned()) {
                    hasUnreturned = true;
                    break;
                }
            }
           
            if (hasUnreturned) {
                System.out.println("Cannot delete user with unreturned items!");
                return;
            }
           
            boolean success = library.deleteUser(userId);
            if (success) {
                System.out.println("User deleted successfully!");
            } else {
                System.out.println("Failed to delete user.");
            }
        } else {
            System.out.println("Deletion cancelled.");
        }
    }
    // ==================== RESOURCE CRUD OPERATIONS ====================
   
    private static void addResource() {
        System.out.println("\n--- Add New Resource ---");
        System.out.println("Resource Type:");
        System.out.println("1. Book");
        System.out.println("2. Journal");
        System.out.println("3. Digital Resource");
        System.out.print("Choose: ");
       
        int type = getIntInput();
       
        System.out.print("Title: ");
        String title = scanner.nextLine();
        System.out.print("Author: ");
        String author = scanner.nextLine();
        System.out.print("Publisher: ");
        String publisher = scanner.nextLine();
        System.out.print("Genre: ");
        String genre = scanner.nextLine();
        System.out.print("ISBN: ");
        String isbn = scanner.nextLine();
       
        int year = 0;
        while (year == 0) {
            System.out.print("Year: ");
            try {
                year = Integer.parseInt(scanner.nextLine());
                if (year < 1000 || year > 2026) {
                    System.out.println("Please enter a valid year (1000-2026)");
                    year = 0;
                }
            } catch (NumberFormatException e) {
                System.out.println("Please enter a valid year number!");
            }
        }
       
        Resource resource = null;
       
        switch (type) {
            case 1:
                int pages = 0;
                while (pages == 0) {
                    System.out.print("Number of Pages: ");
                    try {
                        pages = Integer.parseInt(scanner.nextLine());
                        if (pages <= 0) {
                            System.out.println("Pages must be positive!");
                            pages = 0;
                        }
                    } catch (NumberFormatException e) {
                        System.out.println("Please enter a valid number!");
                    }
                }
                resource = new Book(title, author, publisher, genre, isbn, year, pages);
                break;
            case 2:
                System.out.print("Volume: ");
                String volume = scanner.nextLine();
                System.out.print("Issue: ");
                String issue = scanner.nextLine();
                resource = new Journal(title, author, publisher, genre, isbn, year, volume, issue);
                break;
            case 3:
                System.out.print("File Format: ");
                String format = scanner.nextLine();
                double size = 0;
                while (size == 0) {
                    System.out.print("File Size (MB): ");
                    try {
                        size = Double.parseDouble(scanner.nextLine());
                        if (size <= 0) {
                            System.out.println("Size must be positive!");
                            size = 0;
                        }
                    } catch (NumberFormatException e) {
                        System.out.println("Please enter a valid number!");
                    }
                }
                resource = new DigitalResource(title, author, publisher, genre, isbn, year, format, size);
                break;
            default:
                System.out.println("Invalid type");
                return;
        }
       
        library.addResource(resource);
        System.out.println("Resource added successfully! ID: " + resource.getResourceId());
    }
   
    private static void updateResource() {
        System.out.print("Enter Resource ID to update: ");
        String resourceId = scanner.nextLine();
       
        Resource resource = library.getResource(resourceId);
        if (resource == null) {
            System.out.println("Resource not found!");
            return;
        }
       
        System.out.println("\n--- Updating Resource: " + resource.getTitle() + " ---");
        System.out.println("1. Update Title");
        System.out.println("2. Update Author");
        System.out.println("3. Update Publisher");
        System.out.println("4. Update Genre");
        System.out.println("5. Update Year");
        System.out.println("6. Cancel");
        System.out.print("Choose: ");
       
        int choice = getIntInput();
       
        switch (choice) {
            case 1:
                System.out.print("Enter new title: ");
                resource.setTitle(scanner.nextLine());
                System.out.println("Title updated successfully!");
                break;
            case 2:
                System.out.print("Enter new author: ");
                resource.setAuthor(scanner.nextLine());
                System.out.println("Author updated successfully!");
                break;
            case 3:
                System.out.print("Enter new publisher: ");
                resource.setPublisher(scanner.nextLine());
                System.out.println("Publisher updated successfully!");
                break;
            case 4:
                System.out.print("Enter new genre: ");
                resource.setGenre(scanner.nextLine());
                System.out.println("Genre updated successfully!");
                break;
            case 5:
                System.out.print("Enter new year: ");
                int year = getIntInput();
                resource.setYear(year);
                System.out.println("Year updated successfully!");
                break;
            default:
                System.out.println("Update cancelled.");
        }
    }
   
    private static void removeResource() {
        System.out.print("Enter Resource ID to remove: ");
        String resourceId = scanner.nextLine();
       
        Resource resource = library.getResource(resourceId);
        if (resource == null) {
            System.out.println("Resource not found!");
            return;
        }
       
        System.out.println("Are you sure you want to delete: " + resource.getTitle() + "? (y/n)");
        String confirm = scanner.nextLine();
       
        if (confirm.equalsIgnoreCase("y")) {
            boolean success = library.removeResource(resourceId);
            if (success) {
                System.out.println("Resource removed successfully!");
            } else {
                System.out.println("Resource is currently borrowed and cannot be removed.");
            }
        } else {
            System.out.println("Deletion cancelled.");
        }
    }
   
    private static void viewAllResources() {
        List<Resource> resources = library.getAllResources();
       
        if (resources.isEmpty()) {
            System.out.println("No resources available.");
        } else {
            System.out.println("\n--- All Resources ---");
            for (Resource r : resources) {
                System.out.println(r);
            }
        }
    }
   
    private static void viewAllUsers() {
        List<User> users = library.getAllUsers();
       
        if (users.isEmpty()) {
            System.out.println("No users registered.");
        } else {
            System.out.println("\n--- All Users ---");
            System.out.printf("%-4s %-20s %-13s %-12s %-15s %-28s %-15s\n",
                              "No.", "Name", "User Type", "ID", "Password", "Email", "Phone");
            System.out.println("---- -------------------- ------------- ------------ --------------- ---------------------------- ---------------");
            int count = 1;
            for (User u : users) {
                String displayType = u.getUserType().equals("Librarian") ? "Admin" : 
                                    (u.getUserType().equals("Public Member") ? "Public" : u.getUserType());
                String maskedPassword = maskPassword(u.getPassword());
                String name = u.getName();
                if (name.length() > 20) {
                    name = name.substring(0, 17) + "...";
                }
                String email = u.getEmail();
                if (email.length() > 28) {
                    email = email.substring(0, 25) + "...";
                }
                System.out.printf("%-4d %-20s %-13s %-12s %-15s %-28s %-15s\n",
                                  count, name, displayType, u.getUserId(), maskedPassword, email, u.getPhone());
                count++;
            }
        }
    }
   
    private static void processFinePayments() {
        List<Fine> unpaidFines = library.getAllUnpaidFines();
       
        if (unpaidFines.isEmpty()) {
            System.out.println("No unpaid fines.");
            return;
        }
       
        System.out.println("\n--- Unpaid Fines ---");
        for (Fine f : unpaidFines) {
            System.out.println(f);
        }
       
        System.out.print("Enter Fine ID to process payment: ");
        String fineId = scanner.nextLine();
       
        boolean success = library.processFinePayment(fineId);
        if (success) {
            System.out.println("Fine payment processed successfully!");
        } else {
            System.out.println("Fine not found or already paid.");
        }
    }
    // ==================== REPORTS ====================
   
    private static void generateReports() {
        System.out.println("\n--- Reports ---");
        System.out.println("1. Most Borrowed Resources Report");
        System.out.println("2. Revenue Report (Fines)");
        System.out.println("3. Overdue Items Report");
        System.out.println("4. Active Users Report");
        System.out.print("Choose: ");
        int choice = getIntInput();
       
        switch (choice) {
            case 1:
                library.generateMostBorrowedReport();
                break;
            case 2:
                library.generateRevenueReport();
                break;
            case 3:
                library.generateOverdueReport();
                break;
            case 4:
                library.generateActiveUsersReport();
                break;
            default:
                System.out.println("Invalid choice");
        }
    }
    // ==================== UTILITY METHODS ====================
   
    private static int getIntInput() {
        while (true) {
            try {
                String input = scanner.nextLine().trim();
                if (input.isEmpty()) {
                    System.out.print("Please enter a number: ");
                    continue;
                }
                return Integer.parseInt(input);
            } catch (NumberFormatException e) {
                System.out.print("Please enter a valid number: ");
            }
        }
    }
    
    private static String maskPassword(String password) {
        if (password == null || password.length() <= 4) {
            return password; // If too short, return as is or handle differently
        }
        String firstTwo = password.substring(0, 2);
        String lastTwo = password.substring(password.length() - 2);
        int middleLength = password.length() - 4;
        String middle = "*".repeat(middleLength);
        return firstTwo + middle + lastTwo;
    }
    private static void loadData() {
        try {
            library.loadData();
        } catch (Exception e) {
            System.out.println("No existing data found. Starting with empty system.");
            createDefaultData();
        }
    }
   
    private static void createDefaultData() {
        Librarian admin = new Librarian(DEFAULT_ADMIN_ID, "Admin User", "admin@library.com", "0123456789",
                                        "Library Office", DEFAULT_ADMIN_PASSWORD);
        library.addUser(admin);
       
        User faculty = new User(DEFAULT_FACULTY_ID, "Faculty User", "faculty@test.com", "0123456789",
                                 "Faculty Address", DEFAULT_FACULTY_PASSWORD, "Faculty", 10, 7);
        library.addUser(faculty);
       
        User student = new User(DEFAULT_STUDENT_ID, "Student User", "student@test.com", "0123456789",
                                "Student Address", DEFAULT_STUDENT_PASSWORD, "Student", 3, 7);
        library.addUser(student);
       
        User publicUser = new User(DEFAULT_PUBLIC_ID, "Public User", "public@test.com", "0123456789",
                                   "Public Address", DEFAULT_PUBLIC_PASSWORD, "Public Member", 2, 7);
        library.addUser(publicUser);
       
        User publicFineUser = new User(DEFAULT_PUBLIC_FINE_ID, "Public Fine User", "latepublic@test.com", "0123456789",
                                       "Public Address", DEFAULT_PUBLIC_FINE_PASSWORD, "Public Member", 2, 7);
        library.addUser(publicFineUser);
       
        Book book1 = new Book("Java Programming", "James Gosling", "Oracle Press", "Programming",
                              "978-0134685991", 2020, 1200);
        Book book2 = new Book("Clean Code", "Robert Martin", "Prentice Hall", "Software Engineering",
                              "978-0132350884", 2008, 464);
        Book book3 = new Book("Design Patterns", "Erich Gamma", "Addison-Wesley", "Programming",
                              "978-0201633610", 1994, 395);
        Book book4 = new Book("Effective Java", "Joshua Bloch", "Addison-Wesley", "Programming",
                              "978-0134685991", 2018, 416);
        library.addResource(book1);
        library.addResource(book2);
        library.addResource(book3);
        library.addResource(book4);
       
        Transaction lateReturn = new Transaction(book4.getResourceId(), DEFAULT_PUBLIC_FINE_ID,
                                                 LocalDate.now().minusDays(10), LocalDate.now().minusDays(3));
        lateReturn.setReturnDate(LocalDate.now().minusDays(2));
        lateReturn.setReturned(true);
        lateReturn.setFineAmount(5.00);
        library.addTransaction(lateReturn);
       
        Fine fine = new Fine(lateReturn.getTransactionId(), DEFAULT_PUBLIC_FINE_ID, 5.00, "Overdue return");
        library.addFine(fine);
       
        System.out.println("Default books created!");
    }
    private static void saveData() {
        try {
            library.saveData();
        } catch (Exception e) {
            System.out.println("Error saving data: " + e.getMessage());
        }
    }


    private static void printDefaultUserHint() {
        System.out.println("Available accounts:");
        List<User> users = library.getAllUsers();
        for (User user : users) {
            String displayType = user.getUserType().equals("Librarian") ? "Admin" : 
                                (user.getUserType().equals("Public Member") ? "Public" : user.getUserType());
            System.out.println(displayType + "\t- ID: " + user.getUserId() + ", Password: " + user.getPassword());
        }
    }
}
// ==================== USER CLASSES ====================
class User implements Serializable {
    private static final long serialVersionUID = 1L;
   
    private String userId;
    private String name;
    private String email;
    private String phone;
    private String address;
    private String password;
    private String userType;
    private int borrowLimit;
    private int loanDuration;
   
    public User(String userId, String name, String email, String phone, String address,
                String password, String userType, int borrowLimit, int loanDuration) {
        this.userId = userId;
        this.name = name;
        this.email = email;
        this.phone = phone;
        this.address = address;
        this.password = password;
        this.userType = userType;
        this.borrowLimit = borrowLimit;
        this.loanDuration = loanDuration;
    }
   
    public User(String name, String email, String phone, String address,
                String password, String userType, int borrowLimit, int loanDuration) {
        this("U" + UUID.randomUUID().toString().substring(0, 8).toUpperCase(),
             name, email, phone, address, password, userType, borrowLimit, loanDuration);
    }
   
    public String getUserId() { return userId; }
    public String getName() { return name; }
    public String getEmail() { return email; }
    public String getPhone() { return phone; }
    public String getAddress() { return address; }
    public String getPassword() { return password; }
    public String getUserType() { return userType; }
    public int getBorrowLimit() { return borrowLimit; }
    public int getLoanDuration() { return loanDuration; }
   
    public void setName(String name) { this.name = name; }
    public void setEmail(String email) { this.email = email; }
    public void setPhone(String phone) { this.phone = phone; }
    public void setAddress(String address) { this.address = address; }
    public void setPassword(String password) { this.password = password; }
   
    @Override
    public String toString() {
        return String.format("User[ID=%s, Name=%s, Type=%s, Email=%s, Phone=%s]",
                             userId, name, userType, email, phone);
    }
}
class Librarian extends User {
    private static final long serialVersionUID = 1L;
    private String employeeId;
   
    public Librarian(String userId, String name, String email, String phone, String address, String password) {
        super(userId, name, email, phone, address, password, "Librarian", 999, 14);
        this.employeeId = "EMP" + UUID.randomUUID().toString().substring(0, 6).toUpperCase();
    }


    public Librarian(String name, String email, String phone, String address, String password) {
        super(name, email, phone, address, password, "Librarian", 999, 14);
        this.employeeId = "EMP" + UUID.randomUUID().toString().substring(0, 6).toUpperCase();
    }
   
    public String getEmployeeId() { return employeeId; }
   
    @Override
    public String toString() {
        return String.format("Librarian[ID=%s, Name=%s, EmployeeID=%s, Email=%s]",
                             getUserId(), getName(), employeeId, getEmail());
    }
}
// ==================== RESOURCE CLASSES (Inheritance) ====================
abstract class Resource implements Serializable {
    private static final long serialVersionUID = 1L;
   
    protected String resourceId;
    protected String title;
    protected String author;
    protected String publisher;
    protected String genre;
    protected String isbn;
    protected int year;
    protected boolean available;
    protected LinkedList<String> reservationQueue;
   
    public Resource(String title, String author, String publisher, String genre,
                    String isbn, int year) {
        this.resourceId = "R" + UUID.randomUUID().toString().substring(0, 8).toUpperCase();
        this.title = title;
        this.author = author;
        this.publisher = publisher;
        this.genre = genre;
        this.isbn = isbn;
        this.year = year;
        this.available = true;
        this.reservationQueue = new LinkedList<>();
    }
   
    public String getResourceId() { return resourceId; }
    public String getTitle() { return title; }
    public String getAuthor() { return author; }
    public String getPublisher() { return publisher; }
    public String getGenre() { return genre; }
    public String getIsbn() { return isbn; }
    public int getYear() { return year; }
    public boolean isAvailable() { return available; }
   
    public void setAvailable(boolean available) { this.available = available; }
    public void setTitle(String title) { this.title = title; }
    public void setAuthor(String author) { this.author = author; }
    public void setPublisher(String publisher) { this.publisher = publisher; }
    public void setGenre(String genre) { this.genre = genre; }
    public void setYear(int year) { this.year = year; }
   
    public void addToReservationQueue(String userId) { reservationQueue.add(userId); }
    public String getNextReservation() { return reservationQueue.poll(); }
    public String peekNextReservation() { return reservationQueue.peek(); }
    public boolean hasReservations() { return !reservationQueue.isEmpty(); }
    public boolean hasReservation(String userId) { return reservationQueue.contains(userId); }
   
    public abstract String getResourceType();
   
    @Override
    public String toString() {
        return String.format("[%s] %s by %s (%d) - %s",
                             getResourceType(), title, author, year,
                             available ? "Available" : "On Loan");
    }
}
class Book extends Resource {
    private static final long serialVersionUID = 1L;
    private int pages;
   
    public Book(String title, String author, String publisher, String genre,
                String isbn, int year, int pages) {
        super(title, author, publisher, genre, isbn, year);
        this.pages = pages;
    }
   
    public int getPages() { return pages; }
   
    @Override
    public String getResourceType() { return "Book"; }
   
    @Override
    public String toString() {
        return super.toString() + String.format(" | Pages: %d", pages);
    }
}
class Journal extends Resource {
    private static final long serialVersionUID = 1L;
    private String volume;
    private String issue;
   
    public Journal(String title, String author, String publisher, String genre,
                   String isbn, int year, String volume, String issue) {
        super(title, author, publisher, genre, isbn, year);
        this.volume = volume;
        this.issue = issue;
    }
   
    public String getVolume() { return volume; }
    public String getIssue() { return issue; }
   
    @Override
    public String getResourceType() { return "Journal"; }
   
    @Override
    public String toString() {
        return super.toString() + String.format(" | Vol: %s, Issue: %s", volume, issue);
    }
}
class DigitalResource extends Resource {
    private static final long serialVersionUID = 1L;
    private String fileFormat;
    private double fileSize;
   
    public DigitalResource(String title, String author, String publisher, String genre,
                           String isbn, int year, String fileFormat, double fileSize) {
        super(title, author, publisher, genre, isbn, year);
        this.fileFormat = fileFormat;
        this.fileSize = fileSize;
    }
   
    public String getFileFormat() { return fileFormat; }
    public double getFileSize() { return fileSize; }
   
    @Override
    public String getResourceType() { return "Digital Resource"; }
   
    @Override
    public String toString() {
        return super.toString() + String.format(" | Format: %s, Size: %.1f MB", fileFormat, fileSize);
    }
}
// ==================== TRANSACTION CLASS ====================
class Transaction implements Serializable {
    private static final long serialVersionUID = 1L;
   
    private String transactionId;
    private String resourceId;
    private String userId;
    private LocalDate borrowDate;
    private LocalDate dueDate;
    private LocalDate returnDate;
    private boolean returned;
    private double fineAmount;
   
    public Transaction(String resourceId, String userId, LocalDate borrowDate, LocalDate dueDate) {
        this.transactionId = "T" + UUID.randomUUID().toString().substring(0, 8).toUpperCase();
        this.resourceId = resourceId;
        this.userId = userId;
        this.borrowDate = borrowDate;
        this.dueDate = dueDate;
        this.returned = false;
        this.fineAmount = 0;
    }
   
    public String getTransactionId() { return transactionId; }
    public String getResourceId() { return resourceId; }
    public String getUserId() { return userId; }
    public LocalDate getBorrowDate() { return borrowDate; }
    public LocalDate getDueDate() { return dueDate; }
    public LocalDate getReturnDate() { return returnDate; }
    public boolean isReturned() { return returned; }
    public double getFineAmount() { return fineAmount; }
   
    public void setReturnDate(LocalDate returnDate) { this.returnDate = returnDate; }
    public void setReturned(boolean returned) { this.returned = returned; }
    public void setFineAmount(double fineAmount) { this.fineAmount = fineAmount; }
   
    @Override
    public String toString() {
        return String.format("Transaction[ID=%s, Resource=%s, Due=%s, Returned=%s, Fine=RM%.2f]",
                             transactionId, resourceId, dueDate, returned, fineAmount);
    }
}
// ==================== FINE CLASS ====================
class Fine implements Serializable {
    private static final long serialVersionUID = 1L;
   
    private String fineId;
    private String transactionId;
    private String userId;
    private double amount;
    private String reason;
    private LocalDate issueDate;
    private boolean paid;
   
    public Fine(String transactionId, String userId, double amount, String reason) {
        this.fineId = "F" + UUID.randomUUID().toString().substring(0, 8).toUpperCase();
        this.transactionId = transactionId;
        this.userId = userId;
        this.amount = amount;
        this.reason = reason;
        this.issueDate = LocalDate.now();
        this.paid = false;
    }
   
    public String getFineId() { return fineId; }
    public String getTransactionId() { return transactionId; }
    public String getUserId() { return userId; }
    public double getAmount() { return amount; }
    public String getReason() { return reason; }
    public LocalDate getIssueDate() { return issueDate; }
    public boolean isPaid() { return paid; }
   
    public void setPaid(boolean paid) { this.paid = paid; }
   
    @Override
    public String toString() {
        return String.format("Fine[ID=%s, User=%s, Amount=RM%.2f, Reason=%s, Paid=%s]",
                             fineId, userId, amount, reason, paid);
    }
}
// ==================== LIBRARY CORE CLASS ====================
class Library implements Serializable {
    private static final long serialVersionUID = 1L;
   
    private HashMap<String, User> users;
    private HashMap<String, Resource> resources;
    private HashMap<String, Transaction> transactions;
    private HashMap<String, Fine> fines;
   
    private static final String DATA_DIR = "library_data/";
    private static final double DAILY_FINE_RATE = 1.0;
   
    public Library() {
        users = new HashMap<>();
        resources = new HashMap<>();
        transactions = new HashMap<>();
        fines = new HashMap<>();
    }
   
    // User Management
    public void addUser(User user) {
        users.put(user.getUserId(), user);
    }
   
    public User getUser(String userId) {
        return users.get(userId);
    }
   
    public List<User> getAllUsers() {
        return new ArrayList<>(users.values());
    }
   
    public boolean deleteUser(String userId) {
        User user = users.get(userId);
        if (user == null) {
            return false;
        }
       
        for (Transaction t : transactions.values()) {
            if (t.getUserId().equals(userId) && !t.isReturned()) {
                return false;
            }
        }
       
        users.remove(userId);
        return true;
    }
   
    public User authenticateUser(String userId, String password) {
        User user = users.get(userId);
        if (user != null && user.getPassword().equals(password)) {
            return user;
        }
        return null;
    }
   
    // Resource Management
    public void addResource(Resource resource) {
        resources.put(resource.getResourceId(), resource);
    }
   
    public boolean removeResource(String resourceId) {
        Resource resource = resources.get(resourceId);
        if (resource != null && resource.isAvailable()) {
            resources.remove(resourceId);
            return true;
        }
        return false;
    }
   
    public Resource getResource(String resourceId) {
        return resources.get(resourceId);
    }
   
    public List<Resource> getAllResources() {
        return new ArrayList<>(resources.values());
    }
   
    public List<Resource> searchByTitle(String title) {
        List<Resource> results = new ArrayList<>();
        for (Resource r : resources.values()) {
            if (r.getTitle().toLowerCase().contains(title.toLowerCase())) {
                results.add(r);
            }
        }
        return results;
    }
   
    public List<Resource> searchByAuthor(String author) {
        List<Resource> results = new ArrayList<>();
        for (Resource r : resources.values()) {
            if (r.getAuthor().toLowerCase().contains(author.toLowerCase())) {
                results.add(r);
            }
        }
        return results;
    }
   
    public List<Resource> searchByGenre(String genre) {
        List<Resource> results = new ArrayList<>();
        for (Resource r : resources.values()) {
            if (r.getGenre().toLowerCase().contains(genre.toLowerCase())) {
                results.add(r);
            }
        }
        return results;
    }
   
    public List<Resource> searchByISBN(String isbn) {
        List<Resource> results = new ArrayList<>();
        for (Resource r : resources.values()) {
            if (r.getIsbn().equals(isbn)) {
                results.add(r);
            }
        }
        return results;
    }
   
    public List<Resource> searchResources(String searchTerm) {
        String term = searchTerm.toLowerCase();
        List<Resource> results = new ArrayList<>();
        for (Resource r : resources.values()) {
            if (r.getResourceId().toLowerCase().contains(term)
                || r.getTitle().toLowerCase().contains(term)
                || r.getAuthor().toLowerCase().contains(term)
                || String.valueOf(r.getYear()).contains(term)) {
                results.add(r);
            }
        }
        return results;
    }
   
    // Borrowing and Returning
    public Transaction borrowResource(User user, String resourceId) throws Exception {
        Resource resource = resources.get(resourceId);
       
        if (resource == null) {
            throw new Exception("Resource not found");
        }
       
        if (!resource.isAvailable()) {
            throw new Exception("Resource is not available");
        }
       
        if (resource.hasReservations() && !user.getUserId().equals(resource.peekNextReservation())) {
            throw new Exception("Resource is reserved for another user");
        }
       
        int borrowedCount = 0;
        for (Transaction t : transactions.values()) {
            if (t.getUserId().equals(user.getUserId()) && !t.isReturned()) {
                borrowedCount++;
            }
        }
       
        if (borrowedCount >= user.getBorrowLimit()) {
            throw new Exception("Borrowing limit reached");
        }
       
        for (Fine f : fines.values()) {
            if (f.getUserId().equals(user.getUserId()) && !f.isPaid()) {
                throw new Exception("You have unpaid fines. Please clear them first.");
            }
        }
       
        LocalDate dueDate = LocalDate.now().plusDays(user.getLoanDuration());
        Transaction transaction = new Transaction(resourceId, user.getUserId(), LocalDate.now(), dueDate);
       
        if (resource.hasReservations() && user.getUserId().equals(resource.peekNextReservation())) {
            resource.getNextReservation();
        }
        resource.setAvailable(false);
        transactions.put(transaction.getTransactionId(), transaction);
       
        return transaction;
    }
   
    public Transaction returnResource(User user, String resourceId) throws Exception {
        Transaction activeTransaction = null;
       
        for (Transaction t : transactions.values()) {
            if (t.getResourceId().equals(resourceId) &&
                t.getUserId().equals(user.getUserId()) &&
                !t.isReturned()) {
                activeTransaction = t;
                break;
            }
        }
       
        if (activeTransaction == null) {
            throw new Exception("No active borrowing record found for this resource");
        }
       
        Resource resource = resources.get(resourceId);
        resource.setAvailable(true);
        activeTransaction.setReturnDate(LocalDate.now());
        activeTransaction.setReturned(true);
       
        if (activeTransaction.getDueDate().isBefore(LocalDate.now())) {
            long daysOverdue = ChronoUnit.DAYS.between(activeTransaction.getDueDate(), LocalDate.now());
            double fineAmount = daysOverdue * DAILY_FINE_RATE;
            activeTransaction.setFineAmount(fineAmount);
           
            if (fineAmount > 0) {
                Fine fine = new Fine(activeTransaction.getTransactionId(), user.getUserId(),
                                     fineAmount, "Overdue return");
                fines.put(fine.getFineId(), fine);
            }
        }
       
        return activeTransaction;
    }
   
    public List<Transaction> getUserBorrowedItems(String userId) {
        List<Transaction> userTransactions = new ArrayList<>();
        for (Transaction t : transactions.values()) {
            if (t.getUserId().equals(userId)) {
                userTransactions.add(t);
            }
        }
        return userTransactions;
    }
   
    public void addTransaction(Transaction transaction) {
        transactions.put(transaction.getTransactionId(), transaction);
    }
   
    public void addFine(Fine fine) {
        fines.put(fine.getFineId(), fine);
    }
   
    public boolean reserveResource(User user, String resourceId) {
        Resource resource = resources.get(resourceId);
        if (resource != null && !resource.isAvailable()) {
            if (resource.hasReservation(user.getUserId())) {
                return false;
            }
            resource.addToReservationQueue(user.getUserId());
            return true;
        }
        return false;
    }
   
    // Fine Management
    public List<Fine> getUserFines(String userId) {
        List<Fine> userFines = new ArrayList<>();
        for (Fine f : fines.values()) {
            if (f.getUserId().equals(userId)) {
                userFines.add(f);
            }
        }
        return userFines;
    }
   
    public void payFines(String userId) {
        for (Fine f : fines.values()) {
            if (f.getUserId().equals(userId) && !f.isPaid()) {
                f.setPaid(true);
            }
        }
    }
   
    public boolean processFinePayment(String fineId) {
        Fine fine = fines.get(fineId);
        if (fine != null && !fine.isPaid()) {
            fine.setPaid(true);
            return true;
        }
        return false;
    }
   
    public List<Fine> getAllUnpaidFines() {
        List<Fine> unpaidFines = new ArrayList<>();
        for (Fine f : fines.values()) {
            if (!f.isPaid()) {
                unpaidFines.add(f);
            }
        }
        return unpaidFines;
    }
   
    // Reports
    public void generateMostBorrowedReport() {
        Map<String, Integer> borrowCount = new HashMap<>();
       
        for (Transaction t : transactions.values()) {
            String resourceId = t.getResourceId();
            borrowCount.put(resourceId, borrowCount.getOrDefault(resourceId, 0) + 1);
        }
       
        List<Map.Entry<String, Integer>> sorted = new ArrayList<>(borrowCount.entrySet());
        sorted.sort((a, b) -> b.getValue().compareTo(a.getValue()));
       
        System.out.println("\n=== MOST BORROWED RESOURCES ===");
        System.out.printf("%-15s %-30s %-10s\n", "Resource ID", "Title", "Borrow Count");
        System.out.println("------------------------------------------------");
       
        for (int i = 0; i < Math.min(10, sorted.size()); i++) {
            Map.Entry<String, Integer> entry = sorted.get(i);
            Resource r = resources.get(entry.getKey());
            if (r != null) {
                String title = r.getTitle();
                if (title.length() > 30) title = title.substring(0, 27) + "...";
                System.out.printf("%-15s %-30s %-10d\n",
                                  entry.getKey(), title, entry.getValue());
            }
        }
    }
   
    public void generateRevenueReport() {
        double totalRevenue = 0;
        int paidFines = 0;
       
        for (Fine f : fines.values()) {
            if (f.isPaid()) {
                totalRevenue += f.getAmount();
                paidFines++;
            }
        }
       
        double outstanding = 0;
        for (Fine f : fines.values()) {
            if (!f.isPaid()) {
                outstanding += f.getAmount();
            }
        }
       
        System.out.println("\n=== REVENUE REPORT ===");
        System.out.println("Total fines paid: RM " + totalRevenue);
        System.out.println("Number of fines paid: " + paidFines);
        System.out.println("Outstanding fines: RM " + outstanding);
    }
   
    public void generateOverdueReport() {
        System.out.println("\n=== OVERDUE ITEMS REPORT ===");
        System.out.printf("%-15s %-15s %-15s %-20s\n", "Transaction ID", "User ID", "Resource ID", "Due Date");
        System.out.println("--------------------------------------------------------------------------------");
       
        boolean hasOverdue = false;
        for (Transaction t : transactions.values()) {
            if (!t.isReturned() && t.getDueDate().isBefore(LocalDate.now())) {
                System.out.printf("%-15s %-15s %-15s %-20s\n",
                                  t.getTransactionId(), t.getUserId(), t.getResourceId(),
                                  t.getDueDate().toString());
                hasOverdue = true;
            }
        }
       
        if (!hasOverdue) {
            System.out.println("No overdue items.");
        }
    }
   
    public void generateActiveUsersReport() {
        Map<String, Integer> userActivity = new HashMap<>();
       
        for (Transaction t : transactions.values()) {
            userActivity.put(t.getUserId(), userActivity.getOrDefault(t.getUserId(), 0) + 1);
        }
       
        System.out.println("\n=== ACTIVE USERS REPORT ===");
        System.out.printf("%-15s %-20s %-10s\n", "User ID", "Name", "Borrow Count");
        System.out.println("----------------------------------------");
       
        List<Map.Entry<String, Integer>> sorted = new ArrayList<>(userActivity.entrySet());
        sorted.sort((a, b) -> b.getValue().compareTo(a.getValue()));
       
        for (Map.Entry<String, Integer> entry : sorted) {
            User u = users.get(entry.getKey());
            if (u != null) {
                String name = u.getName();
                if (name.length() > 20) name = name.substring(0, 17) + "...";
                System.out.printf("%-15s %-20s %-10d\n",
                                  entry.getKey(), name, entry.getValue());
            }
        }
    }
   
    // Data Persistence
    public void saveData() throws IOException {
        File dir = new File(DATA_DIR);
        if (!dir.exists()) {
            dir.mkdir();
        }
       
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(DATA_DIR + "users.dat"))) {
            oos.writeObject(new ArrayList<>(users.values()));
        }
       
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(DATA_DIR + "resources.dat"))) {
            oos.writeObject(new ArrayList<>(resources.values()));
        }
       
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(DATA_DIR + "transactions.dat"))) {
            oos.writeObject(new ArrayList<>(transactions.values()));
        }
       
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(DATA_DIR + "fines.dat"))) {
            oos.writeObject(new ArrayList<>(fines.values()));
        }
    }
   
    @SuppressWarnings("unchecked")
    public void loadData() throws IOException, ClassNotFoundException {
        File dir = new File(DATA_DIR);
        if (!dir.exists()) {
            throw new FileNotFoundException("Data directory not found");
        }
       
        File usersFile = new File(DATA_DIR + "users.dat");
        if (usersFile.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(usersFile))) {
                List<User> userList = (List<User>) ois.readObject();
                for (User u : userList) {
                    users.put(u.getUserId(), u);
                }
            }
        }
       
        File resourcesFile = new File(DATA_DIR + "resources.dat");
        if (resourcesFile.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(resourcesFile))) {
                List<Resource> resourceList = (List<Resource>) ois.readObject();
                for (Resource r : resourceList) {
                    resources.put(r.getResourceId(), r);
                }
            }
        }
       
        File transactionsFile = new File(DATA_DIR + "transactions.dat");
        if (transactionsFile.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(transactionsFile))) {
                List<Transaction> transactionList = (List<Transaction>) ois.readObject();
                for (Transaction t : transactionList) {
                    transactions.put(t.getTransactionId(), t);
                }
            }
        }
       
        File finesFile = new File(DATA_DIR + "fines.dat");
        if (finesFile.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(finesFile))) {
                List<Fine> fineList = (List<Fine>) ois.readObject();
                for (Fine f : fineList) {
                    fines.put(f.getFineId(), f);
                }
            }
        }
    }
}

