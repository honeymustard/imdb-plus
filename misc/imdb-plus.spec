Name:           imdb-plus
Version:        X.X.X
Release:        1%{?dist}
Summary:        Tis great..

License:        GPLv3+
URL:            https://github.com/honeymustard/imdb-plus
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  pkgconfig
BuildRequires:  gtk2-devel >= %{gtk2_version}
BuildRequires:  libcurl-devel >= %{libcurl_version}

%description
awesome

%prep
%setup -n %{name}-%{version} -q

%build
make clean
make %{?_smp_mflags}

%install 
rm -rf %{buildroot}
make DESTDIR=%{buildroot} install

%files
%doc TODO
%{_mandir}/man1/%{name}.1.gz
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/%{name}/res
%{_datadir}/pixmaps

%clean
rm -rf %{buildroot}

%changelog
* Wed Oct 02 2012 Honeymustard <adrian.solumsmo@gmail.com>
- Created first RPM for Fedora

