CREATE DATABASE `sekolah`;
USE `sekolah`;

CREATE TABLE `kelas` (
    `ID_Kelas` INT(16) NOT NULL,
    `Nama_Kelas` VARCHAR(256) NOT NULL,
    `Wali_Kelas` VARCHAR(256) NOT NULL,
    PRIMARY KEY (`ID_Kelas`)
);

CREATE TABLE `siswa` (
    `ID_Siswa` INT(16) NOT NULL,
    `Nama_Siswa` VARCHAR(256) NOT NULL,
    `Tanggal_Lahir` DATE NOT NULL,
    `Jenis_Kelamin` VARCHAR(1) NOT NULL,
    `ID_Kelas` INT(16) NOT NULL,
    PRIMARY KEY (`ID_Siswa`),
    FOREIGN KEY (`ID_Kelas`) REFERENCES `kelas`(`ID_KELAS`)
);

INSERT INTO `kelas` (`ID_Kelas`, `Nama_Kelas`, `Wali_Kelas`)
VALUES
    (1, 'Kelas 1', 'Pak Andi'),
    (2, 'Kelas 2', 'Bu Siti'),
    (3, 'Kelas 3', 'Pak Budi');

INSERT INTO `siswa` (`ID_Siswa`, `Nama_Siswa`, `Tanggal_Lahir`, `Jenis_Kelamin`, `ID_Kelas`)
VALUES
    (1, 'Ahmad', '2005-01-15', 'L', 1),
    (2, 'Budi',  '2006-02-20', 'L', 1),
    (3, 'Cindy', '2005-03-10', 'P', 2),
    (4, 'Dina',  '2006-04-25', 'P', 2),
    (5, 'Eido',  '2005-05-30', 'L', 3);