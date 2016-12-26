Summary: A chess program with configurable AI
Name: cheops
Version: 1.3
Release: 0
License: GPL-3.0+
Group: Amusements/Games/Board/Chess
URL: https://logological.org/%{name}
Source0: https://files.nothingisreal.com/software/%{name}/%{name}-%{version}.tar.bz2
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: gcc-c++
BuildRequires: gzip

%description
CHEOPS (CHEss OPponent Simulator) is a fully-functional chess program
capable of human-vs-human, human-vs-computer, and computer-vs-computer
play. It uses a 64-square linear array board representation. The game
tree search is alpha-beta, and the static evaluation function
considers material, mobility, and motif features.

%prep
%setup -q

%build
%{_configure} --prefix=%{_prefix}
%{__make}

%install
[ "%{buildroot}" != "/" ] && %{__rm} -rf %{buildroot}
%{__make} DESTDIR=%{buildroot} install-strip

%clean
[ "%{buildroot}" != "/" ] && %{__rm} -rf %{buildroot}


%files
%defattr(-,root,root,-)
%{_bindir}/cheops
%doc AUTHORS COPYING INSTALL NEWS README.md THANKS doc/cheops.pdf
%doc %{_mandir}/man6/cheops.6.gz



%changelog
* Mon Dec 26 2016 Tristan Miller <psychonaut@nothingisreal.com> - 
- Initial build.

