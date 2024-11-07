<?= $this->extend('layouts/default') ?>

<?= $this->section('content') ?>
<style>
  td.actions {
    display: flex;
    gap: .5rem;

    form {
      width: fit-content;

      button {
        --bt-color: #dc3545;
        margin-bottom: 0;
        background-color: var(--bt-color);
        border-color: var(--bt-color);

        &:hover,
        &:focus,
        &:active {
          --bt-color: #b02a37;
        }
      }
    }
  }
</style>

<main class="container">
  <div style="display: flex; justify-content: space-between; align-items: end;">
    <h1>Daftar Produk</h1>
    <a href="products/new" role="button">Tambah</a>
  </div>
  <table class="striped">
    <thead>
      <tr>
        <th scope="col">Kode</th>
        <th scope="col">Nama</th>
        <th scope="col">Harga/kg</th>
        <th scope="col">Aksi</th>
      </tr>
    </thead>
    <tbody>
      <?php foreach ($products as $product): ?>
        <?php $price = number_format(floatval($product['price']), 0, null, '.') ?>
        <tr>
          <th scope="row">
            <?= $product['code'] ?>
          </th>
          <td>
            <?= $product['name'] ?>
          </td>
          <td>
            <?= "Rp$price,00" ?>
          </td>
          <td class="actions">
            <a href="/products/<?= $product['code'] ?>/edit" role="button">Ubah</a>
            <form action="/products/<?= $product['code'] ?>" method="post" data-type="delete" data-code="<?= $product['code'] ?>" data-name="<?= $product['name'] ?>">
              <input type="hidden" name="_method" value="DELETE">
              <button type="submit">Hapus</button>
            </form>
          </td>
        </tr>
      <?php endforeach; ?>
    </tbody>
  </table>

  <div style="width: fit-content; margin-left: auto">
    <a href="/products/<?= $pagination['page'] > 2 ? '?page=' . intval($pagination['page']) - 1 : '' ?>" <?= !$pagination['previous'] ? 'disabled' : '' ?> role="button">
      &lsaquo; Previous
    </a>
    <select name="page" data-current="<?= $pagination['page'] ?>" required style="width: fit-content; margin-bottom: 0; margin-inline: .5rem">
      <?php for ($i = 1; $i <= $pagination['all_pages']; $i++): ?>
        <?php $selected = $i == $pagination['page'] ? 'selected disabled' : ''; ?>
        <option value="<?= $i ?>" <?= $selected ?>><?= $i ?></option>
      <?php endfor; ?>
    </select>
    <a href="/products/?page=<?= intval($pagination['page']) + 1 ?>" <?= !$pagination['next'] ? 'disabled' : '' ?> role="button">
      Next &rsaquo;
    </a>
  </div>
</main>

<script>
  const deleteForms = document.querySelectorAll('td.actions form[data-type=delete]')

  deleteForms.forEach((deleteForm) => {
    deleteForm.addEventListener('submit', function (event) {
      event.preventDefault()
      if (confirm(`Apa Anda ingin menghapus ${this.dataset.name}?\n(Kode ${this.dataset.code})`)) {
        this.submit()
      }
    })
  })
</script>
<?= $this->endSection() ?>