Summary: UDP client VMOD for Varnish.
Name: vmod-dgram
Version: 0.2
Release: 1%{?dist}
License: BSD
Group: System Environment/Daemons
Source0: libvmod-dgram.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish >= 4.0.2
BuildRequires: make
BuildRequires: python-docutils
BuildRequires: varnish >= 4.0.2
BuildRequires: varnish-libs-devel >= 4.0.2

%description
UDP client VMOD for Varnish

%prep
%setup -n libvmod-dgram

%build
%configure --prefix=/usr/
%{__make} %{?_smp_mflags}
%{__make} %{?_smp_mflags} check

%install
[ %{buildroot} != "/" ] && %{__rm} -rf %{buildroot}
%{__make} install DESTDIR=%{buildroot}

%clean
[ %{buildroot} != "/" ] && %{__rm} -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_libdir}/varnish/vmods/
%doc /usr/share/doc/%{name}/*
%{_mandir}/man?/*

%changelog
* Web Aug 4 2015 Maksim Naumov - 0.2
- Rebuild for Varnish 4.0
* Thu May 30 2013 Matthew M. Boedicker <matthewm@boedicker.org> - 0.1-0.20130530
- Initial version.
