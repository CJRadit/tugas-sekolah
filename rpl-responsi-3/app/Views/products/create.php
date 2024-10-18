<?= $this->extend('layouts/app') ?>

<?= $this->section('page_title') ?>
  Tambah Produk
<?= $this->endSection() ?>

<?= $this->section('content') ?>
  <main class="container">
    <h1>Tambah Produk</h1>

    <?php if (!empty($session) && !empty($session->getFlashdata('error'))): ?>
      <?= $session->getFlashdata('error') ?>
    <?php endif ?>

    <?php if (!empty(validation_errors())): ?>
      <?php foreach (validation_errors() as $name => $message): ?>
        <div class="p-4 mb-4 text-sm text-red-800 rounded-lg bg-red-50 dark:bg-gray-800 dark:text-red-400" role="alert">
          <?= $message ?>
        </div>
      <?php endforeach ?>
    <?php endif ?>

    <?= form_open('products') ?>
      <fieldset>
        <label>
          Kode
          <input
            type="number"
            min="0"
            name="code"
            placeholder="Kode"
            autocomplete="off"
            value="<?= old('code') ?>"
            required
          />
        </label>
        <label>
          Nama
          <input
            name="name"
            placeholder="Nama"
            autocomplete="off"
            value="<?= old('name') ?>"
            required
          />
        </label>
        <label>
          Harga
          <input
            type="number"
            min="0"
            name="price"
            placeholder="Nama"
            autocomplete="off"
            value="<?= old('price') ?>"
            required
          />
        </label>
      </fieldset>

      <input
        type="submit"
        value="Tambah"
      />
    <?= form_close() ?>
  </main>
<?= $this->endSection() ?>
