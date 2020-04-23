/*
Work on 3 tables of the form Ta(aid, a2, …), Tb(bid, b2, …), Tc(cid, aid, bid, …), where:

aid, bid, cid, a2, b2 are integers;
the primary keys are underlined;
a2 is UNIQUE in Ta;
aid and bid are foreign keys in Tc, referencing the corresponding primary keys in Ta and Tb, respectively.
a. Write queries on Ta such that their execution plans contain the following operators:

clustered index scan;
clustered index seek;
nonclustered index scan;
nonclustered index seek;
key lookup.
b. Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan. Create a nonclustered index that can speed up the query. Recheck the query’s execution plan (operators, SELECT’s estimated subtree cost).

c. Create a view that joins at least 2 tables. Check whether existing indexes are helpful; if not, reassess existing indexes / examine the cardinality of the tables.
*/

--- LAPTOPS(LID, Price, Model Number), CUSTOMER(CID, Name, Age), SALE(SID, LID, CID, ShopID)

CREATE DATABASE ComputerShop
GO

USE ComputerShop
GO

CREATE TABLE Laptops(
LaptopID INT PRIMARY KEY IDENTITY(1,1),
Price INT,
Brand VARCHAR(20),
Model INT UNIQUE)

CREATE TABLE Customer(
CustomerID INT PRIMARY KEY IDENTITY(1,1),
Name VARCHAR(20),
Age INT NOT NULL)

CREATE TABLE Sale(
SaleID INT PRIMARY KEY IDENTITY(1,1),
LaptopID INT FOREIGN KEY REFERENCES Laptops(LaptopID),
CustomerID INT FOREIGN KEY REFERENCES Customer(CustomerID),
Quantity INT)

INSERT INTO Laptops VALUES (100, 'Lenovo', 510), (200, 'Lenovo', 530), (150, 'Dell', 1500), (400, 'Macbook', 2100), (300, 'Huawei', 4300)
INSERT INTO Customer VALUES ('Oana', 20), ('Mara', 20), ('Geo', 19), ('Dan', 22), ('Radu', 21), ('Daria', 19),('Maria', 18),('Mihai', 21),('Paul', 20),('Mihnea', 23),('Stefan', 22),('Alina', 18),('Ema', 19),('Robi', 24),('Elena', 25),('Andrei', 25)
INSERT INTO Sale VALUES (1,1,1),(1,2,1),(1,3,1),(1,4,1),(2,5,1),(2,3,1),(2,1,1)


SELECT * FROM Laptops
SELECT * FROM Customer
SELECT * FROM Sale

--- a.

--- clustered index scan
SELECT * FROM Laptops

--- non clustered index scan & key lookup 
SELECT * FROM Laptops ORDER BY Model

--- clustered index seek
SELECT * FROM Laptops INNER JOIN Sale ON Laptops.LaptopID = Sale.LaptopID
SELECT * FROM Laptops WHERE LaptopID = 5

--- non-clustered index seek & key lookup
SELECT * FROM Laptops WHERE Model = 510

--- b.
IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'N_Index_Customer')
DROP INDEX N_Index_Customer ON Customer

SELECT * FROM Customer WHERE Age = 20

CREATE NONCLUSTERED INDEX N_Index_Customer ON Customer(Age)
GO
SELECT Age FROM Customer WHERE Age = 20
GO

--- c.
CREATE VIEW CustomerView
AS
SELECT Laptops.Brand, Laptops.Price, Customer.Name, Customer.Age FROM Customer INNER JOIN Sale ON Customer.CustomerID = Sale.CustomerID INNER JOIN Laptops ON Sale.LaptopID = Laptops.LaptopID

GO

SELECT * FROM CustomerView