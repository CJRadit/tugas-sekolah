CREATE DATABASE `tshz`;
USE `tshz`;

CREATE TABLE `golongan` (
    `kode` VARCHAR(16) NOT NULL,
    `gaji_pokok` INT(16) NOT NULL,
    `tunjangan` INT(16) NOT NULL,
    PRIMARY KEY (`kode`)
);

CREATE TABLE `bagian` (
    `kode` VARCHAR(16) NOT NULL,
    `nama` VARCHAR(256) NOT NULL,
    PRIMARY KEY (`kode`)
);

CREATE TABLE `karyawan` (
    `nik` VARCHAR(16) NOT NULL,
    `kode_bagian` VARCHAR(16) NOT NULL,
    `kode_golongan` VARCHAR(16) NOT NULL,
    `nama` VARCHAR(256) NOT NULL,
    `kota` VARCHAR(256) NOT NULL,
    PRIMARY KEY (`nik`),
    FOREIGN KEY (`kode_bagian`) REFERENCES `bagian`(`kode`),
    FOREIGN KEY (`kode_golongan`) REFERENCES `golongan`(`kode`)
);

INSERT INTO `golongan` (`kode`, `gaji_pokok`, `tunjangan`)
VALUES
    ('3A', 7000000, 1500000),
    ('3B', 5000000, 1000000),
    ('3C', 4000000,  750000);

INSERT INTO `bagian` (`kode`, `nama`)
VALUES
    ('01PRO', 'Project'                  ),
    ('02OAM', 'Operation and Maintenance'),
    ('03FIN', 'Finance'                  ),
    ('04BGD', 'Budget'                   ),
    ('05MKT', 'Marketing'                );

INSERT INTO `karyawan` (`nik`, `kode_bagian`, `kode_golongan`, `nama`, `kota`)
VALUES
    ('2022PROJ001', '01PRO', '3A', 'Wisno', 'Semarang'  ),
    ('2022PROJ002', '01PRO', '3B', 'Agus' , 'Magelang'  ),
    ('2022PROJ003', '01PRO', '3B', 'Dila' , 'Jakarta'   ),
    ('2022OM001'  , '02OAM', '3A', 'Doni' , 'Semarang'  ),
    ('2022OM002'  , '02OAM', '3B', 'Eka'  , 'Semarang'  ),
    ('2022OM003'  , '02OAM', '3C', 'Rizki', 'Purwokerto');