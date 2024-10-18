<?php

namespace App\Controllers;

use App\Controllers\BaseController;
use App\Models\Product;

class ProductController extends BaseController
{
    protected $helpers = ['form', 'validation_errors', 'old'];

    public function index()
    {
        $product = new Product();

        return view('products/index', [ 'products' => $product->findAll() ]);
    }

    public function new()
    {
        return view('products/create');
    }

    public function create()
    {
        $request = $this->request->getPost();        
        $rules = [
            'code'  => 'required|integer|greater_than_equal_to[0]|is_unique[products.code]',
            'name'  => 'required|string|max_length[255]',
            'price' => 'required|integer|greater_than_equal_to[0]',
        ];

        if (!$this->validateData($request, $rules)) {
            return redirect()->back()->withInput();
        }

        $product = new Product();
        try {
            $product->insert($request);
        } catch (\ReflectionException $ex) {
            return redirect()->back()->with('error', $ex);
        }
        return $this->index();
    }
}
