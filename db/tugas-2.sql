CREATE TABLE `supplier` (
    `scode` VARCHAR(2) NOT NULL,
    `sname` VARCHAR(255) NOT NULL,
    `status` INT(16) NOT NULL,
    `city` VARCHAR(255) NOT NULL,
    PRIMARY KEY (`scode`)
);

CREATE TABLE `parts` (
    `pcode` VARCHAR(2) NOT NULL,
    `spame` VARCHAR(255) NOT NULL,
    `color` VARCHAR(255) NOT NULL,
    `weight` INT(16) NOT NULL,
    `city` VARCHAR(255) NOT NULL,
    PRIMARY KEY (`pcode`)
);

CREATE TABLE `shipment` (
    `scode` VARCHAR(2) NOT NULL,
    `pcode` VARCHAR(2) NOT NULL,
    `qty` INT(16) NOT NULL
);

INSERT INTO `supplier`
VALUES
    ('S1', 'ARIS',   20, 'Semarang'),
    ('S2', 'EKO',    10, 'Jakarta'),
    ('S3', 'BETA',   30, 'Surabaya'),
    ('S4', 'KOLIK',  20, 'Medan'),
    ('S5', 'SHINTA', 30, 'Yogyakarta');

INSERT INTO `parts`
VALUES
    ('P1', 'NUT',   'Merah', 12, 'Semarang'),
    ('P2', 'BOLT',  'Hijau', 17, 'Jakarta'),
    ('P3', 'SCREW', 'Biru',  17, 'Jakarta'),
    ('P4', 'SCREW', 'Merah', 14, 'Semarang'),
    ('P5', 'CAM',   'Biru',  12, 'Semarang'),
    ('P6', 'COG',   'Merah', 19, 'Jakarta');

INSERT INTO `shipment`
VALUES
    ('S1', 'P1', 300),
    ('S1', 'P2', 200),
    ('S1', 'P3', 400),
    ('S1', 'P4', 200),
    ('S1', 'P5', 100),
    ('S1', 'P6', 100),
    ('S2', 'P1', 300),
    ('S2', 'P2', 400),
    ('S3', 'P2', 200),
    ('S4', 'P2', 200),
    ('S4', 'P4', 300),
    ('S4', 'P5', 400);