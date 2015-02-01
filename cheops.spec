Summary: A chess program with configurable AI
Name: cheops
Version: 1.2
Release: 1
License: GPL
Group: Amusements/Games/Board/Chess
URL: http://www.nothingisreal.com/cheops/
Source0: http://www.nothingisreal.com/cheops/%{name}-%{version}.tar.bz2
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
Prefix: %{_prefix}

%description
CHEOPS (CHEss OPponent Simulator) is a fully-functional chess program
capable of human-vs-human, human-vs-computer, and computer-vs-computer
play. It uses a 64-square linear array board representation. The game
tree search is alpha-beta, and the static evaluation function
considers material, mobility, and motif features.

%prep
%setup -q

%build
./configure --prefix=%{_prefix}
make

%install
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install-strip

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%{_prefix}/bin/cheops
%doc ChangeLog AUTHORS COPYING INSTALL NEWS README THANKS doc/cheops.pdf doc/cheops.dvi
%doc %{_prefix}/man/man6/cheops.6.gz



%changelog
* Fri Dec  4 2004 Tristan Miller <psychonaut@nothingisreal.com> - 
- Initial build.

