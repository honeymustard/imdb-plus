## README for imdb-plus

**imdb-plus** is currently under development, and as such only provides limited functionality.

This means that if you were to attempt to compile the sources at any given point in time <br />
they might not be entirely up to speed, which is to say that **it might be complete bunk**. <br />

## Compilation instructions

**Linux:**

    # Note: Requires GTK+, libcurl
    
    $ make
    $ sudo make install
    
    or
    
    $ make build                  # builds src/.deb packages
    
**Windows:**

    # Note: Requires MinGW, GTK+, GnuWin32 PCRE, Libcurl. See Makefile.
    
    $ mingw32-make mingw32        # builds imdb-plus.exe
    
    or 
    
    # Note: Requires Inno Setup 5, 7-zip command-line version (7za.exe). See Makefile
    
    $ mingw32-make mingw32        # builds imdb-plus.exe
    $ mingw32-make mingw32-build  # builds src, dist, and setup archives..

## Screenshots

<table>
 <tr>
  <td><b>imdb-plus on debian 1</b></td>
  <td><b>imdb-plus on debian 2</b></td>
 </tr>
 <tr>
  <td>
   <img width="280" height="200" 
    src="https://github.com/honeymustard/imdb-plus/raw/master/local/ss-linux-1.png" 
    alt="imdb-plus on debian"
   />
  </td>
  <td>
   <img width="280" height="200" 
    src="https://github.com/honeymustard/imdb-plus/raw/master/local/ss-linux-2.png" 
    alt="imdb-plus on debian"
   />
  </td>
 </tr>
</table>