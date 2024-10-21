<?php

namespace App\Controllers;

use App\Controllers\BaseController;
use App\Models\Product;

class ProductController extends BaseController
{
    public function index()
    {
        $product = new Product();

        return view('products/index', [ 'products' => $product->findAll() ]);
    }
}
