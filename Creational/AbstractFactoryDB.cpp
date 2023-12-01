/* This example will be an Abstract Factory for handling Database connections
 * with MySQL, PostgreSQL, and Oracle.
 *
 * Abstract Factory Class -> DatabaseFactory
 * Abstract Product Classes -> DatabaseConnection & DatabaseCommand
 * Concrete Factories -> MySQLFactory & PostgreSQLFactory & OracleFactory
 * Concrete Product Classes ->  MySQLConnection & MySQLCommand
 *                              PostgreSQLConnection & PostgreSQLCommand
 *                              OracleConnection & OracleCommand
 */

#include <memory>
#include <string>

// Abstract Products and Factory
class DatabaseConnection {
  public:
    virtual ~DatabaseConnection() = default;
    virtual void connect() = 0;
};

class DatabaseCommand {
  public:
    virtual ~DatabaseCommand() = default;
    virtual void execute(const std::string& query) = 0;
};

class DatabaseFactory {
  public:
    virtual ~DatabaseFactory() = default;
    virtual std::unique_ptr<DatabaseConnection> createConnection() = 0;
    virtual std::unique_ptr<DatabaseCommand> createCommand() = 0;
};

// MySQL concrete Products and Factory
class MySQLConnection : public DatabaseConnection {
  public:
    void connect() override {
      // logic for connecting to the MySQL database here.
    }
};

class MySQLCommand : public DatabaseCommand {
  public:
    void execute(const std::string& query) override {
      // logic for executing MySQL commands here.
    }
};

class MySQLFactory : public DatabaseFactory {
  public:
    std::unique_ptr<DatabaseConnection> createConnection() override {
      return std::make_unique<MySQLConnection>();
    }

    std::unique_ptr<DatabaseCommand> createCommand() override {
      return std::make_unique<MySQLCommand>();
    }
};

// PostgreSQL concrete Products and Factory
class PostgreSQLConnection : public DatabaseConnection {
  public:
    void connect() override {
      // logic for connecting to the PostgreSQL database here.
    }
};

class PostgreSQLCommand : public DatabaseCommand {
  public:
    void execute(const std::string& query) override {
      // logic for executing PostgreSQL commands here.
    }
};

class PostgreSQLFactory : public DatabaseFactory {
  public:
    std::unique_ptr<DatabaseConnection> createConnection() override {
      return std::make_unique<PostgreSQLConnection>();
    }

    std::unique_ptr<DatabaseCommand> createCommand() override {
      return std::make_unique<PostgreSQLCommand>();
    }
};

// Oracle concrete Products and Factory
class OracleConnection : public DatabaseConnection {
  public:
    void connect() override {
      // logic for connecting to the Oracle database here.
    }
};

class OracleCommand : public DatabaseCommand {
  public:
    void execute(const std::string& query) override {
      // logic for executing Oracle commands here.
    }
};

class OracleFactory : public DatabaseFactory {
  public:
    std::unique_ptr<DatabaseConnection> createConnection() override {
      return std::make_unique<OracleConnection>();
    }

    std::unique_ptr<DatabaseCommand> createCommand() override {
      return std::make_unique<OracleCommand>();
    }
};

int main() {
  std::unique_ptr<DatabaseFactory> factory;

  // Select database type using preprocessing directives

#ifdef ORACLE
  factory = std::make_unique<OracleFactory>();
#elif defined(POSTGRES)
  factory = std::make_unique<PostgreSQLFactory>();
#else  // MySQL
  factory = std::make_unique<MySQLFactory>();
#endif

  std::unique_ptr<DatabaseConnection> connection = factory->createConnection();
  std::unique_ptr<DatabaseCommand> command = factory->createCommand();

  connection->connect();
  command->execute("SELECT * FROM some_table");

  return 0;
}
