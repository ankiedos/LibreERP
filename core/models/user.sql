CREATE TABLE `users` (
    id INT PRIMARY KEY NOT NULL UNIQUE AUTO_INCREMENT,
    name TINYTEXT NOT NULL,
    second_name TINYTEXT,
    surname TINYTEXT NOT NULL,
    gender INT(2) NOT NULL,
    password_hash TINYTEXT NOT NULL,
    address_id INT FOREIGN KEY(`addresses`) NOT NULL,
    email_id INT FOREIGN KEY(`emails`) NOT NULL UNIQUE,
    role_id INT FOREIGN KEY(`roles`) NOT NULL
);