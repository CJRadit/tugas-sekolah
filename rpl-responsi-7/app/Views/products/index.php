<?php
$query = ['search' => $_GET['search'] ?? null];

$previous_query = $pagination['page'] > 2
  ? [
    'page' => intval($pagination['page']) - 1,
    'search' => $_GET['search'] ?? null
  ]
  : null;
$next_query = [
  'page' => intval($pagination['page']) + 1,
  'search' => $_GET['search'] ?? null
];
?>

<?= $this->extend('layouts/default') ?>

<?= $this->section('content') ?>
<style>
  tr th {
    text-align: center;

    &:not(:nth-child(2)) {
      width: 0.1%;
      white-space: nowrap;
    }
  }

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
  <!-- Heading, Search, & Add -->
  <div style="display: flex; justify-content: space-between; align-items: center;">
    <h1>Daftar Produk</h1>

    <div style="display: flex; gap: .5rem; align-items: start;">
      <!-- Search -->
      <form id="_search" action="/products" method="GET">
        <fieldset role="group">
          <input
            type="text"
            name="search"
            placeholder="Cari"
            autocomplete="search"
            title="Cari"
            <?php if (isset($_GET['search'])): ?> value="<?= $_GET['search'] ?>" <?php endif ?>
          />
          <button type="submit" style="padding: .75rem 1rem">
            <svg xmlns="http://www.w3.org/2000/svg" width="28" height="28" fill="#ffffff" viewBox="0 0 256 256"><path d="M229.66,218.34l-50.07-50.06a88.11,88.11,0,1,0-11.31,11.31l50.06,50.07a8,8,0,0,0,11.32-11.32ZM40,112a72,72,0,1,1,72,72A72.08,72.08,0,0,1,40,112Z"></path></svg>
          </button>
        </fieldset>
      </form>

      <!-- Add -->
      <a href="/products/new" role="button" title="Tambah">
        <svg xmlns="http://www.w3.org/2000/svg" width="28" height="28" fill="#ffffff" viewBox="0 0 256 256"><path d="M224,128a8,8,0,0,1-8,8H136v80a8,8,0,0,1-16,0V136H40a8,8,0,0,1,0-16h80V40a8,8,0,0,1,16,0v80h80A8,8,0,0,1,224,128Z"></path></svg>
      </a>
    </div>
  </div>

  <!-- Table -->
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
            <a href="/products/<?= $product['code'] ?>/edit" role="button" title="Ubah">
              <svg xmlns="http://www.w3.org/2000/svg" width="28" height="28" fill="#ffffff" viewBox="0 0 256 256"><path d="M227.31,73.37,182.63,28.68a16,16,0,0,0-22.63,0L36.69,152A15.86,15.86,0,0,0,32,163.31V208a16,16,0,0,0,16,16H92.69A15.86,15.86,0,0,0,104,219.31L227.31,96a16,16,0,0,0,0-22.63ZM92.69,208H48V163.31l88-88L180.69,120ZM192,108.68,147.31,64l24-24L216,84.68Z"></path></svg>
            </a>
            <form action="/products/<?= $product['code'] ?>" method="post" data-type="delete" data-code="<?= $product['code'] ?>" data-name="<?= $product['name'] ?>">
              <input type="hidden" name="_method" value="DELETE">
              <button type="submit" title="Hapus">
                <svg xmlns="http://www.w3.org/2000/svg" width="28" height="28" fill="#ffffff" viewBox="0 0 256 256"><path d="M216,48H40a8,8,0,0,0,0,16h8V208a16,16,0,0,0,16,16H192a16,16,0,0,0,16-16V64h8a8,8,0,0,0,0-16ZM192,208H64V64H192ZM80,24a8,8,0,0,1,8-8h80a8,8,0,0,1,0,16H88A8,8,0,0,1,80,24Z"></path></svg>
              </button>
            </form>
          </td>
        </tr>
      <?php endforeach; ?>
    </tbody>
  </table>

  <!-- Pagination -->
  <div style="display: flex; width: fit-content; margin-inline: auto">
    <a
      href="/products<?= !empty($previous_query) ? '?' . http_build_query($previous_query) : '' ?>"
      role="button"
      title="Sebelumnya"
      <?= !$pagination['previous'] ? 'disabled' : '' ?>
    >
      &lsaquo;
    </a>

    <select
      name="page"
      data-current="<?= $pagination['page'] ?>"
      title="Pilih halaman"
      required
      style="width: fit-content; margin-bottom: 0; margin-inline: .5rem"
    >
      <?php for ($i = 1; $i <= $pagination['all_pages']; $i++): ?>
        <?php $selected = $i == $pagination['page'] ? 'selected disabled' : ''; ?>
        <option value="<?= $i ?>" <?= $selected ?>><?= $i ?></option>
      <?php endfor; ?>
    </select>

    <a
      href="/products?<?= http_build_query($next_query) ?>"
      role="button"
      title="Selanjutnya"
      <?= !$pagination['next'] ? 'disabled' : '' ?>
    >
      &rsaquo;
    </a>
  </div>
</main>

<script>
  // Search
  const searchForm = document.querySelector('#_search')
  console.log(searchForm.querySelector('input[name=search]').value)
  searchForm.addEventListener('submit', function (event) {
    event.preventDefault()
    if (this.querySelector('input[name=search]').value) return this.submit()
    window.location.href = `/products`
  })

  // Delete
  const deleteForms = document.querySelectorAll('td.actions form[data-type=delete]')
  deleteForms.forEach((deleteForm) => {
    deleteForm.addEventListener('submit', function (event) {
      event.preventDefault()
      if (confirm(`Apa Anda ingin menghapus ${this.dataset.name}?\n(Kode ${this.dataset.code})`)) {
        this.submit()
      }
    })
  })

  // Pagination Select
  const paginationSelect = document.querySelector('select[name=page]')
  paginationSelect.addEventListener('change', function () {
    const page = parseInt(this.value)
    if (!page) {
      console.error("Invalid value.")
      return
    }
    if (page == this.dataset.current) {
      return
    }

    window.location.href = page >= 2
      ? `/products?page=${page}`
      : `/products`
  })
</script>
<?= $this->endSection() ?>