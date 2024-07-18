CREATE DATABASE `KLINIKSEHAT`;
USE `KLINIKSEHAT`;

CREATE TABLE `PASIEN` (
    `ID_Pasien`     INT(16)      NOT NULL AUTO_INCREMENT,
    `Nama_Pasien`   VARCHAR(255) NOT NULL,
    `Tanggal_Lahir` DATE         NOT NULL,
    `Jenis_Kelamin` VARCHAR(1)   NOT NULL,
    `Alamat`        VARCHAR(255) NOT NULL,
    PRIMARY KEY (`ID_Pasien`)
);

CREATE TABLE `KUNJUNGAN` (
    `ID_Kunjungan`      INT(16)      NOT NULL AUTO_INCREMENT,
    `ID_Pasien`         INT(16)      NOT NULL,
    `Tanggal_Kunjungan` DATE         NOT NULL,
    `Dokter`            VARCHAR(255) NOT NULL,
    `Diagnosa`          VARCHAR(255) NOT NULL,
    PRIMARY KEY (`ID_Kunjungan`)
);

INSERT INTO `PASIEN` (`ID_Pasien`, `Nama_Pasien`, `Tanggal_Lahir`, `Jenis_Kelamin`, `Alamat`)
VALUES
    (1, 'Siti', '1990-01-15', 'P', 'Jakarta'   ),
    (2, 'Budi', '1985-02-20', 'L', 'Bandung'   ),
    (3, 'Adi',  '1995-03-10', 'P', 'Surabaya'  ),
    (4, 'Dedi', '1975-04-25', 'L', 'Medan'     ),
    (5, 'Eko',  '1980-05-30', 'L', 'Yogyakarta');

INSERT INTO `KUNJUNGAN` (`ID_Kunjungan`, `ID_Pasien`, `Tanggal_Kunjungan`, `Dokter`, `Diagnosa`)
VALUES
    (1, 1, '2023-07-01', 'Dr. Andi', 'Flu'       ),
    (2, 3, '2023-07-05', 'Dr. Siti', 'Deman'     ),
    (3, 4, '2023-07-07', 'Dr. Budi', 'Hipertensi'),
    (4, 1, '2023-07-10', 'Dr. Andi', 'Batuk'     ),
    (5, 2, '2023-07-12', 'Dr. Siti', 'Diabetes'  );