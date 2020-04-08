CREATE DATABASE ManagementSys;

USE ManagementSys;

CREATE TABLE UserInfo(
    UserName VARCHAR(12) PRIMARY KEY,
    Pwd VARCHAR(12) NOT NULL,
    Since DATE NOT NULL,
    LastLogin DATETIME,
    Signature VARCHAR(50),
    IsAd INT CHECK(IsAd=0 OR IsAd=1),
)

CREATE TABLE Moment(
    UserName VARCHAR(12),
    PublicDate SMALLDATETIME PRIMARY KEY,
    Context VARCHAR(200),
    IsReview INT CHECK(IsReview=0 OR IsReview=1),
)
