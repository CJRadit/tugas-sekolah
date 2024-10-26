<?php $update ??= false ?>

<?= $this->extend("layouts/default") ?>

<?= $this->section('content') ?>
<main class="container">
  <?php if (!$update): ?>
    <h1>Tambah Produk</h1>
  <?php else: ?>
    <h1>Ubah Produk</h1>
  <?php endif ?>

  <?= validation_list_errors() ?>

  <form action="<?= !$update ? '/products' : '/products/' . $data['code'] ?>" method="POST">
    <?= csrf_field() ?>
    <?php if ($update): ?>
      <input type="hidden" name="_method" value="PATCH">
    <?php endif ?>

    <fieldset>
      <?php if (!$update): ?>
        <label>
          Kode
          <input type="number" min="10000" max="99999" name="code" placeholder="Kode" autocomplete="" value="<?= old('code') ?>" />
        </label>
      <?php endif ?>
      <label>
        Nama
        <input name="name" placeholder="Nama" autocomplete="" value="<?= $update ? $data['name'] : old('name') ?>" />
      </label>
      <label>
        Harga/kg
        <input type="number" name="price" placeholder="Harga/kg" autocomplete="" value="<?= $update ? $data['price'] : old('price') ?>" />
      </label>
    </fieldset>

    <input type="submit" value="<?= $update ? 'Ubah' : 'Tambah' ?>" />
  </form>
</main>
<?= $this->endSection() ?>