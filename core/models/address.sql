CREATE TABLE `addresses` (
    id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
    country TINYTEXT NOT NULL,
    region TINYTEXT NOT NULL,
    city TINYTEXT NOT NULL,
    street TINYTEXT NOT NULL,
    building VARCHAR(4) NOT NULL,
    apartment VARCHAR(6) NOT NULL,
    postal_code CHAR(6) NOT NULL
);