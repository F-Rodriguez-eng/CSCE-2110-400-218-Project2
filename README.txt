# CSCE-2110-400-218-Project2
Project 2: Smart Campus Navigation and Facility Analytic System

This is a program that reads the campus information from the text files and enable users to locate facilities, build connections, find routes and be able to view summary reports.The program uses three main data structures:
-A custom hash table for facility lookup by ID.
-An undirected graph for campus buildings and walkways, including Breadth-First Search (BFS).
-A general tree for the academic department hierarchy.

The project implements a custom hash table with the collision handling to allow efficient data searching. It uses both the undirected graph and BFS to explore connections, and find the short path.

Team Members

Brenda Cheruiyot
Michael Oke
Fernando Rodriguez

Features Implemented
Facility Management
-Facility Search-ID
                -Name
                -Category
-Facility Viewing
-Category reports

Hash Table
-Custom hash function
-Collision handling
-Facility ID lookup

Graph
-Building and work connections
-Shotest path searching
-Connectivity functions

Department Hierarchy
-Tree structure

File management
-Reading the campus data from the text files
-  Validating records

Files in the project
Main.cpp-Has the main menu and controls the whole program



