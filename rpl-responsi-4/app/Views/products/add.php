<?= $this->extend("layouts/default") ?>

<?= $this->section('content') ?>
  <main class="container">
    <h1>Daftar Produk</h1>
    <?= validation_list_errors() ?>
    <form action="/products" method="POST">
      <?= csrf_field() ?>
      <fieldset>
        <label>
          Kode
          <input
            type="number"
            min="10000"
            max="99999"
            name="code"
            placeholder="Kode"
            autocomplete=""
            value="<?= old('code') ?>"
          />
        </label>
        <label>
          Nama
          <input
            name="name"
            placeholder="Nama"
            autocomplete=""
            value="<?= old('name') ?>"
          />
        </label>
        <label>
          Harga/kg
          <input
            type="number"
            name="price"
            placeholder="Harga/kg"
            autocomplete=""
            value="<?= old('price') ?>"
          />
        </label>
      </fieldset>

      <input
        type="submit"
        value="Tambah"
      />
    </form>
  </main>
<?= $this->endSection() ?>
