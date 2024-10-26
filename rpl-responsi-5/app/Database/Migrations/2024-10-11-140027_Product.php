<?php

namespace App\Database\Migrations;

use CodeIgniter\Database\Migration;

class Product extends Migration
{
    public function up()
    {
        $this->forge->addField([
            'code' => [
                'type' => 'INT',
                'constraint' => 5,
                'unsigned' => true,
                'autoIncrement' => true
            ],
            'name' => [
                'type' => 'VARCHAR',
                'constraint' => 50,
            ],
            'price' => [
                'type' => 'VARCHAR',
                'constraint' => 50,
            ]
        ]);
        $this->forge->addPrimaryKey('code');
        $this->forge->createTable('products');
    }

    public function down()
    {
        $this->forge->dropTable('products');
    }
}
