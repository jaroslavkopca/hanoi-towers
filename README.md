<html lang="en">
<body>
    <h1>Hanoi Tower Game in C++</h1>

    <h2>Table of Contents</h2>
    <ul>
        <li><a href="#introduction">Introduction</a></li>
        <li><a href="#features">Features</a></li>
        <li><a href="#technologies">Technologies</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#usage">Usage</a></li>
        <li><a href="#how-it-works">How It Works</a></li>
        <li><a href="#contributing">Contributing</a></li>
        <li><a href="#license">License</a></li>
    </ul>

    <h2 id="introduction">Introduction</h2>
    <p>The Hanoi Tower Game is a C++ implementation of the classic puzzle game. The game consists of three towers and a number of disks of different sizes which can slide onto any tower. The puzzle starts with the disks in a neat stack in ascending order of size on one tower, the smallest at the top, thus making a conical shape. The objective of the game is to move the entire stack to another tower, obeying the following simple rules:</p>
    <ol>
        <li>Only one disk can be moved at a time.</li>
        <li>Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack or on an empty rod.</li>
        <li>No disk may be placed on top of a smaller disk.</li>
    </ol>

    <h2 id="features">Features</h2>
    <ul>
        <li><strong>Basic Game Play</strong>: Users can move disks between towers.</li>
        <li><strong>Visual Representation</strong>: A simple console-based UI to represent towers and disks.</li>
        <li><strong>Error Checking</strong>: Ensures moves are legal according to game rules.</li>
        <li><strong>Move Counter</strong>: Tracks the number of moves made by the player.</li>
    </ul>

    <h2 id="technologies">Technologies</h2>
    <ul>
        <li><strong>C++</strong>: The project is entirely written in C++.</li>
        <li><strong>CMake</strong>: Used for building and compiling the project.</li>
        <li><strong>Standard Template Library (STL)</strong>: Utilizes C++ STL for data handling and manipulation.</li>
    </ul>

    <h2 id="installation">Installation</h2>
    <h3>Prerequisites</h3>
    <ul>
        <li>C++ Compiler (GCC recommended)</li>
        <li>CMake</li>
    </ul>

    <h3>Building the Project</h3>
    <ol>
        <li>Clone the repository to your local machine.</li>
        <li>Navigate to the project directory.</li>
        <li>

Run cmake . to generate the Makefile.</li>
<li>Build the project using make.</li>
</ol>

php

<h2 id="usage">Usage</h2>
<p>To play the game, run the executable generated after building the project. The game starts with a default number of disks, but this can be changed via command line arguments.</p>

<h3>Command Line Arguments</h3>
<p><code>./HanoiTowerGame [number_of_disks]</code> - Starts the game with the specified number of disks.</p>

<h3>Game Play</h3>
<ul>
    <li>The game will display the current state of the towers and ask for the player's input.</li>
    <li>Input the source and destination towers as prompted.</li>
    <li>The game will move the disk if the move is legal and update the tower's state.</li>
    <li>The game ends when all disks are moved to another tower.</li>
</ul>

<h2 id="how-it-works">How It Works</h2>
<ul>
    <li><strong>Disk</strong>: Represents the individual disks. Each disk has a size attribute.</li>
    <li><strong>Tower</strong>: Represents the towers. Each tower holds a stack of disks.</li>
    <li><strong>Game</strong>: Manages the game's state and rules.</li>
    <li><strong>GameController</strong>: Handles user input and communicates between the Game and GameView.</li>
    <li><strong>GameView</strong>: Responsible for displaying the current state of the game to the player.</li>
</ul>

<h2 id="contributing">Contributing</h2>
<p>Contributions to this project are welcome. To contribute:</p>
<ol>
    <li>Fork the repository.</li>
    <li>Create a new branch for your feature (<code>git checkout -b feature/YourFeature</code>).</li>
    <li>Commit your changes (<code>git commit -am 'Add some feature'</code>).</li>
    <li>Push to the branch (<code>git push origin feature/YourFeature</code>).</li>
    <li>Open a new Pull Request.</li>
</ol>

<h2 id="license">License</h2>
<p>This project is licensed under the <a href="LICENSE.md">MIT License</a>. See the LICENSE file for more details.</p>

</body>
</html>
