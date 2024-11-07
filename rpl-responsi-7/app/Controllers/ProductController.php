<?php

namespace App\Controllers;

use App\Controllers\BaseController;
use App\Models\Product;

class ProductController extends BaseController
{
    public $helpers = ['form'];

    public function index()
    {
        $product = new Product();

        $paginate = 3;
        $page = intval($this->request->getGet('page') ?? 1);
        $search = $this->request->getGet('search');
        if ($search) {
            $product->like('code', "%$search%")
                ->orLike('name', "%$search%")
                ->orLike('price', "$search%");
        }

        $count_all = $product->countAllResults(false);
        $result = $product->findAll($paginate, ($page - 1) * $paginate);
        $count_result = count($result) + ($page - 1) * $paginate;

        return view('products/index', [
            'products' => $result,
            'pagination' => [
                'page' => $page,
                'all_pages' => intval(ceil($count_all / $paginate)),
                'previous' => $page <= 1 ? false : true,
                'next' => $count_result < $count_all
            ]
        ]);
    }

    public function new()
    {
        return view('products/add');
    }

    public function create()
    {
        if (!$this->request->is('post')) {
            return response()
                ->setBody('HTTP Method not allowed')
                ->setStatusCode(405);
        }

        $rules = [
            'code' => 'required|integer|greater_than[9999]|less_than[100000]|is_unique[products.code]',
            'name' => 'required|string',
            'price' => 'required|integer|greater_than_equal_to[0]'
        ];

        $data = $this->request->getPost(array_keys($rules));
        if (!$this->validateData($data, $rules)) {
            return redirect()->back()->withInput();
        }

        try {
            $validData = $this->validator->getValidated();
            (new Product())->insert($validData);
        } catch (\ReflectionException $_ex) {
            return redirect()->back()->withInput();
        }
        return redirect("ProductController::index");
    }

    public function edit(int $id)
    {
        $data = (new Product())->find($id);
        if (!$data) {
            return redirect('ProductController::index');
        }

        return view('products/add', [
            'update' => true,
            'data' => $data
        ]);
    }

    public function update(int $id)
    {
        if (!($this->request->is(type: 'put') || $this->request->is(type: 'patch'))) {
            return response()
                ->setBody('HTTP Method not allowed')
                ->setStatusCode(405);
        }

        $rules = [
            'name' => 'required|string',
            'price' => 'required|integer|greater_than_equal_to[0]'
        ];

        $data = $this->request->getPost(array_keys($rules));
        if (!$this->validateData($data, $rules)) {
            return redirect()->back()->withInput();
        }

        try {
            $validData = $this->validator->getValidated();
            (new Product())->update($id, $validData);
        } catch (\ReflectionException $_ex) {
            return redirect()->back()->withInput();
        }
        return redirect("ProductController::index");
    }

    public function delete(int $id)
    {
        try {
            (new Product())->delete($id);
        } catch (\InvalidArgumentException $_ex) {
            // 
        }
        return redirect("ProductController::index");
    }
}
