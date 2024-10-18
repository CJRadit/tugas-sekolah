<?php

namespace App\Database\Seeds;

use App\Models\Product;
use CodeIgniter\Database\Seeder;

class ProductSeeder extends Seeder
{
    public function run()
    {
        $products = [
            [
                'code' => 10001,
                'name' => 'Tomat',
                'price' => '1000'
            ],
            [
                'code' => 10002,
                'name' => 'Semangka',
                'price' => '20000'
            ]
        ];
        (new Product())->insertBatch($products);
    }
}
