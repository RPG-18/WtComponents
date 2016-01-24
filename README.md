# WtComponents
Additional classes for Wt

# Components

* simple *FileSystemModel*;
* simple *FileDialog*;
* Wizard & WizardPage.

# Requires

* GNU/Linux
* Wt >= 3.3
* Boost.Filesystem

# Run example

    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_INSTALL_PREFIX=~/tmp/WtComponents ..
    $ make && make install
    $ cd ~/tmp/WtComponents/dist/
    $ ./component-gallery --docroot=. --http-port=8080 --http-address=0.0.0.0

