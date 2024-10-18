<?= $this->extend('layouts/app') ?>

<?= $this->section('page_title') ?>
Daftar Produk
<?= $this->endSection() ?>

<?= $this->section('content') ?>
<main class="container">
  <div style="display: flex">
    <h1 style="flex-grow: 1">Daftar Produk</h1>
    <a href="/products/new" role="button">Tambah</a>
  </div>
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
<?= $this->endSection() ?>
