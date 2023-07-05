/*
 * The abstract factory pattern is a creational pattern that provides an
 * interface for creating families of related or dependent objects without
 * specifying their concrete classes.
 *
 * A couple examples where the Abstract Factory design pattern could be best
 * utilized in C++ is:
 *
 * Cross-Platform UI Elements:
 *  When creating a cross-platform UI toolkit where multiple families of
 *  products like Buttons, Menus, and Dialogs must have different versions
 *  depending on different client platforms (e.g. Windows, Linux, MacOS).
 *  
 *  Each platform would have it's own concrete factory interface that creates
 *  Buttons, Menus, and Dialogs. That way when creating UI elements, the
 *  application code only intefaces with the abstract factory and doesn't
 *  know the specific factory and product classes.
 *
 *  This design allows the easy addition of new platforms or UI elements
 *  without modifying the existing application code. For example, if you
 *  decided to add support for another OS (TempleOS ftw), you would just create
 *  a new factory class for that OS.
 *
 * Database Connectivity:
 *  When creating a database management system that needs to provide
 *  connectivity to multiple databases (e.g. MySQL, PostgreSQL, Oracle), an
 *  Abstract Factory could be used to create objects related to database
 *  connectivity.
 *
 *  An abstract factory interface would create Connection and Command objects,
 *  with each database type having its own concrete factory (MySQLFactory,
 *  PostgreSQLFactory, OracleFactory). When an application wants to interact
 *  with a database, it uses the abstract factory interface and is unaware
 *  of the specific factory and object classes.
 *
 *  This allows for easy addition of new database types/operations wihtout
 *  changing the existing code. For instance, adding support for MariaDB would
 *  mean adding a new factory class (MariaDBFactory).
 *
 * Pros:
 *  -> Certainty that products of a factory are compatible with one another
 *  -> Avoids tight coupling between concrete products and client code
 *  -> Single Resposibility Priciple: keeps creation code in one place
 *     to ease support
 *  -> Open/Closed Priciple: new variants can be introduced without breaking
 *     existing client code
 *
 * Cons:
 *  -> Code may be more complicated than it should be due to abstraction bloat
 */

#include <iostream>

// Cross-Platform UI Element example for Windows/Mac/Linux and Buttons/Menus/Diags

// Define abstract elements and factory interface

class Button {
    public:
        virtual void draw() = 0; // pure virtual function
};

class Menu {
    public:
        virtual void draw() = 0; // pure virtual function
};

class Dialog {
    public:
        virtual void draw() = 0; // pure virtual function
};

class GUIFactory {
    public:
        virtual Button* createButton() = 0;
        virtual Menu* createMenu() = 0;
        virtual Dialog* createDialog() = 0;
};

// Concrete element classes for Windows, Linux, and MacOS:

class WindowsButton : public Button {
    public:
        void draw() override {
            std::cout << "WindowsButton\n";
        }
};

class WindowsMenu : public Menu {
    public:
        void draw() override {
            std::cout << "WindowsMenu\n";
        }
};

class WindowsDialog : public Dialog {
    public:
        void draw() override {
            std::cout << "WindowsDialog\n";
        }
};

class LinuxButton : public Button {
    public:
        void draw() override {
            std::cout << "LinuxButton\n";
        }
};

class LinuxMenu : public Menu {
    public:
        void draw() override {
            std::cout << "LinuxMenu\n";
        }
};

class LinuxDialog : public Dialog {
    public:
        void draw() override {
            std::cout << "LinuxDialog\n";
        }
};

class MacOSButton : public Button {
    public:
        void draw() override {
            std::cout << "MacOSButton\n";
        }
};

class MacOSMenu : public Menu {
    public:
        void draw() override {
            std::cout << "MacOSMenu\n";
        }
};

class MacOSDialog : public Dialog {
    public:
        void draw() override {
            std::cout << "MacOSDialog\n";
        }
};

// Expanding concrete Factory classes to create new types

class WindowsFactory : public GUIFactory {
    public:
        Button* createButton() override {
            return new WindowsButton();
        }

        Menu* createMenu() override {
            return new WindowsMenu();
        }

        Dialog* createDialog() override {
            return new WindowsDialog();
        }
};

class LinuxFactory : public GUIFactory {
    public:
        Button* createButton() override {
            return new LinuxButton();
        }

        Menu* createMenu() override {
            return new LinuxMenu();
        }

        Dialog* createDialog() override {
            return new LinuxDialog();
        }
};

class MacOSFactory : public GUIFactory {
    public:
        Button* createButton() override {
            return new MacOSButton();
        }

        Menu* createMenu() override {
            return new MacOSMenu();
        }

        Dialog* createDialog() override {
            return new MacOSDialog();
        }
};

int main() {
    GUIFactory* factory;
    Button* button;
    Menu* menu;
    Dialog* dialog;

    // Config factory and products based on preprocessor directives
    #ifdef WINDOWS
        factory = new WindowsFactory();
    #elif defined(LINUX)
        factory = new LinuxFactory();
    #else //MacOS
        factory = new MacOSFactory();
    #endif

    button = factory->createButton();
    menu = factory->createMenu();
    dialog = factory->createDialog();

    button->draw();
    menu->draw();
    dialog->draw();


    // Remembering to manually call delete has an inherent risk for memory leaks.
    // Future refactoring should be done to used smart pointers to eliminate
    // the need to allocate memory via new/delete
    delete dialog;
    delete menu;
    delete button;
    delete factory;



    return 0;
}
