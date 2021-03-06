Summary: A GTK+ theme engine
Name: crux
Version: 1.9.3
Release: 1
Copyright: GPL
Group: User Interface/Desktops
Source: %{name}-%{version}.tar.gz
URL: http://www.eazel.com/
Packager: John Harper <jsh@eazel.com>
Buildroot: /var/tmp/%{name}-root
BuildPrereq: gtk+-devel gdk-pixbuf-devel glib-devel gnome-libs-devel libglade-devel

%description
A GTK+ theme engine developed by Eazel, Inc.

%prep
%setup -q
%build

LC_ALL=""
LINGUAS=""
LANG=""
export LC_ALL LINGUAS LANG

%configure

make host_type=%{target_platform}

%install
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf $RPM_BUILD_ROOT
make install \
    DESTDIR=$RPM_BUILD_ROOT \
    host_type=%{_target_platform}

%clean
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc AUTHORS ChangeLog NEWS README THANKS TODO
%{_libdir}/gtk-2.0/2.0.0/engines
%{_datadir}/eazel-engine
%{_datadir}/themes
#%{_datadir}/control-center/Desktop/eazel-engine-properties.desktop
#%{_datadir}/gnome/apps/Settings/Desktop/eazel-engine-properties.desktop
#%{_bindir}/eazel-engine-capplet
