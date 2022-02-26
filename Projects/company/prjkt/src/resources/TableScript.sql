DROP TABLE Billing_Package CASCADE CONSTRAINTS;
DROP TABLE User_details CASCADE CONSTRAINTS;
DROP TABLE sessiondetails CASCADE CONSTRAINTS;

CREATE TABLE Billing_Package(
	packages VARCHAR2(20),
	dataInGB NUMBER(5),
	monthlyCharges NUMBER(3),
	chargesAfterLimit NUMBER(5,3),
	CONSTRAINT pk_Billing_Package_package PRIMARY KEY(packages)
);

INSERT INTO Billing_Package VALUES('MomNDad',2,10,0.01);
INSERT INTO Billing_Package VALUES('SocialTeen',5,15,0.008);
INSERT INTO Billing_Package VALUES('VideoMate',10,20,0.005);
INSERT INTO Billing_Package VALUES('TorrentGuy',20,30,0.002);

CREATE TABLE User_details(
	mac VARCHAR2(20),
	userName VARCHAR2(20) NOT NULL unique,
	fullName VARCHAR2(20) not null,
	password VARCHAR2(20) NOT NULL,
	role VARCHAR(2) check(role in ('A','C')),
	contactno VARCHAR2(10),
	address VARCHAR2(100),
	emailid VARCHAR2(20),
	packages VARCHAR2(12),
	CONSTRAINT pk_User_details PRIMARY KEY(mac),
	constraint fk_User_details FOREIGN KEY(packages) REFERENCES Billing_Package(packages) 
);

INSERT INTO User_details VALUES ('1','Jason','Json Brody','admin','A',7418562648,'Chennai','jason51@gmail.com',null);
INSERT INTO User_details VALUES ('2','Admin','Jason Statham','admin','A',8745213698,'Mysore','jason52@gmail.com',null);
INSERT INTO User_details VALUES ('AC-80-39-7B-DB-47','Tony','Tony Stark','user','C',7452365412,'Delhi','tim123@billing.com','VideoMate');
INSERT INTO User_details VALUES ('00-00-39-AB-D4-53','John','John Mcclane','user','C',9452362147,'Mumbai','john113@billinh.com','MomNDad');
INSERT INTO User_details VALUES ('0D-A0-33-AB-F4-53','Bruce','Bruce Wayne','user','C',9012456321,'Punjab','bruce53@billing.com','VideoMate');
INSERT INTO User_details VALUES ('AE-00-39-AB-D4-53','Angelina','Angelina Jolie','user','C',5412369874,'Pune','jolie413@billinh.com','TorrentGuy');
INSERT INTO User_details VALUES ('CD-A6-69-AB-D4-53','AlphaGo','AlphaGo Zero','user','C',1231231233,'California','alphago@billing.com','SocialTeen');

CREATE TABLE sessiondetails (
sessionid NUMBER(10) CONSTRAINT sess_pk PRIMARY KEY,
mac VARCHAR2(25) NOT NULL,
ip VARCHAR2(25) NOT NULL,
download NUMBER(12) NOT NULL,
upload NUMBER(12) NOT NULL,
total NUMBER(12) NOT NULL,
startDate VARCHAR2(25) NOT NULL,
endDate VARCHAR2(25) NOT NULL,
sessiondate date ,
constraint fk_sessiondetails FOREIGN KEY(mac) REFERENCES User_details(mac)
);


INSERT INTO sessiondetails VALUES(1,'AC-80-39-7B-DB-47','114.23.24.8',225, 10, 235,'27-Aug-2018','27-Aug-2018',DATE '2018-8-27');
INSERT INTO sessiondetails VALUES(2,'00-00-39-AB-D4-53','115.23.24.8',221, 50, 271,'27-Aug-2018','27-Aug-2018',DATE '2018-8-27');
INSERT INTO sessiondetails VALUES(3,'0D-A0-33-AB-F4-53','116.23.24.8',758, 20, 778,'27-Aug-2018','27-Aug-2018',DATE '2018-8-27');
INSERT INTO sessiondetails VALUES(4,'AE-00-39-AB-D4-53','115.23.24.8',221, 50, 271,'27-Aug-2018','27-Aug-2018',DATE '2018-8-27');
INSERT INTO sessiondetails VALUES(5,'CD-A6-69-AB-D4-53','116.23.24.8',758, 20, 778,'27-Aug-2018','27-Aug-2018',DATE '2018-8-27');


COMMIT;

select * from Billing_Package;
select * from User_details;
SELECT * FROM sessiondetails order by sessionid;

