<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Daftar Produk</title>

  <link
    rel="stylesheet"
    href="https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.min.css"
  >
</head>
<body>
  <main class="container">
    <h1>Daftar Produk</h1>
    <table class="striped">
      <thead>
        <tr>
          <th scope="col">Kode</th>
          <th scope="col">Nama</th>
          <th scope="col">Harga/kg</th>
        </tr>
      </thead>
      <tbody>
        <?php foreach ($products as $product): ?>
          <tr>
            <th scope="row"><?= $product['code'] ?></th>
            <td><?= $product['name'] ?></td>
            <td><?= 'Rp' . number_format(floatval($product['price']), thousands_separator: '.') . ',00' ?></td>
          </tr>
        <?php endforeach ?>
      </tbody>
    </table>
  </main>
</body>
</html>