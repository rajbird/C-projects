using System;
using System.Collections.Generic;

namespace InventoryManagementSystem
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Product> products = new List<Product>();
            string choice = "";

            while (choice != "5")
            {
                Console.WriteLine("Welcome to the Inventory Management System!");
                Console.WriteLine("1. Add product");
                Console.WriteLine("2. View products");
                Console.WriteLine("3. Edit product");
                Console.WriteLine("4. Delete product");
                Console.WriteLine("5. Exit");
                Console.WriteLine("Enter your choice: ");
                choice = Console.ReadLine();

                switch (choice)
                {
                    case "1":
                        AddProduct(products);
                        break;
                    case "2":
                        ViewProducts(products);
                        break;
                    case "3":
                        EditProduct(products);
                        break;
                    case "4":
                        DeleteProduct(products);
                        break;
                    case "5":
                        Console.WriteLine("Exiting...");
                        break;
                    default:
                        Console.WriteLine("Invalid choice. Please try again.");
                        break;
                }
            }
        }

        static void AddProduct(List<Product> products)
        {
            Console.WriteLine("Enter product name: ");
            string name = Console.ReadLine();

            Console.WriteLine("Enter product price: ");
            double price = double.Parse(Console.ReadLine());

            Console.WriteLine("Enter product quantity: ");
            int quantity = int.Parse(Console.ReadLine());

            products.Add(new Product(name, price, quantity));
        }

        static void ViewProducts(List<Product> products)
        {
            Console.WriteLine("Product Name\tPrice\tQuantity");
            Console.WriteLine("--------------------------------------");

            foreach (Product p in products)
            {
                Console.WriteLine($"{p.Name}\t\t{p.Price}\t{p.Quantity}");
            }
        }

        static void EditProduct(List<Product> products)
        {
            Console.WriteLine("Enter product name: ");
            string name = Console.ReadLine();

            Product product = products.Find(p => p.Name == name);

            if (product == null)
            {
                Console.WriteLine("Product not found.");
                return;
            }

            Console.WriteLine("Enter new product name (or press enter to skip): ");
            string newName = Console.ReadLine();

            if (!string.IsNullOrEmpty(newName))
            {
                product.Name = newName;
            }

            Console.WriteLine("Enter new product price (or press enter to skip): ");
            string newPrice = Console.ReadLine();

            if (!string.IsNullOrEmpty(newPrice))
            {
                product.Price = double.Parse(newPrice);
            }

            Console.WriteLine("Enter new product quantity (or press enter to skip): ");
            string newQuantity = Console.ReadLine();

            if (!string.IsNullOrEmpty(newQuantity))
            {
                product.Quantity = int.Parse(newQuantity);
            }
        }

        static void DeleteProduct(List<Product> products)
        {
            Console.WriteLine("Enter product name: ");
            string name = Console.ReadLine();

            Product product = products.Find(p => p.Name == name);

            if (product == null)
            {
                Console.WriteLine("Product not found.");
                return;
            }

            products.Remove(product);
        }
    }

    class Product
    {
        public string Name { get; set; }
        public double Price { get; set; }
        public int Quantity { get; set; }

        public Product(string name, double price, int quantity)
        {
            Name = name;
            Price = price;
            Quantity = quantity;
        }
    }
}
