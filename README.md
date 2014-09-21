
<table>
 <tr>
  <td bgcolor="#EEEEFF"><b>imdb-plus on debian</b></td>
  <td bgcolor="#EEEEFF"><b>imdb-plus on fedora</b></td>
  <td bgcolor="#EEEEFF"><b>imdb-plus on windows</b></td>
 <tr>
  <td>
   <img width="210" height="140" 
    src="https://github.com/honeymustard/imdb-plus/raw/master/local/ss-debian.png" 
    alt="imdb-plus on debian"
   />
  </td>
  <td>
   <img width="210" height="140" 
    src="https://github.com/honeymustard/imdb-plus/raw/master/local/ss-fedora.png" 
    alt="imdb-plus on fedora"
   />
  </td>
  <td>
   <img width="210" height="140" 
    src="https://github.com/honeymustard/imdb-plus/raw/master/local/ss-windows.png" 
    alt="imdb-plus on windows"
   />
  </td>
 </tr>
</table>

## Features

* Download and view personal vote history and statistics..
* Download IMDb movie lists and compare them to your vote history..
* Download official IMDb lists such as Top 250, Bottom 100, All-Time Boxoffice.
* Compare personal vote history to IMDb lists and view intersection statistics.
* Supports vote histories with north of 100 000 votes..
* View updated statistics for all official lists, and track your progress..

## Binaries

Binaries are **currently unavailable**. project is unstable.

## Compilation instructions

**Linux:**

    # Note: Requires GTK+3, libcurl
    
    $ make
    $ sudo make install

    or

    $ make build-deb    # builds debian package
    $ make build-rpm    # builds redhat package
    
**Windows:**

    # Note: See Makefile for package requirements
    
    $ mingw32-make mingw32-make     # builds imdb-plus.exe

    or

    $ mingw32-make mingw32-build    # builds setup archive

    # If MinGW complains about errors in winnt.h you should 
    # remove the 'static' bit from the offending functions.
    # Usually: GetCurrentFiber, GetFiberData, NtCurrentTeb
    
## Copyright

Copyright &copy; 2011-2014 Adrian Solumsmo. See [LICENSE](https://github.com/honeymustard/imdb-plus/blob/master/LICENSE) for details.

