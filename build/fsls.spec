### FSLS RPM SPEC
## @file fsls.spec

### RPM SPEC files are called with variables externally defined.
##  Use the `--define` flag to set the following as appropriate:
##
## _version  = Major.Minor.Micro version string
## _buildnum = build number
##

### The external variables, above, will be fleshed out here in the GLOBALs
##
%global version_string	%{_version}
%global _basedir	usr/local
%global _bindir		%{_basedir}/bin
%global _mandir		%{_basedir}/man
%global name		fsls
%global build_name	%{name}-%{version_string}

Name:		   %{name}
Version:	   %{version_string}
Release:	   %{_buildnum}
Summary:	   Fast/Filesystem List

Group:		   Applications/Productivity
License:	   ISC Open Source
URL:		   https://github.com/wgdavies/fs-utils
Source0:	   %{build_name}.tar.gz
#Requires:	   


### Free-form package description.
##
%description
Fast/Filesystem List prints directory statistics, specifically with file
counting in mind, very fast relative to standard filesystem utilities. 

### Keep things clean between builds. 
##
%clean
%{__rm} -rf %{buildroot}
%{__rm} -rf $RPM_BUILD_ROOT

### RPM performs certain general package operations that we don't need to change.
##
%prep
%setup -q
%build


### Simple installation script; builds install directory for package.
##
%install
%{__rm} -rf %{buildroot}
%{__rm} -rf $RPM_BUILD_ROOT
%{__mkdir} -p %{buildroot}/%{_bindir}
%{__mkdir} -p %{buildroot}/%{_mandir}
%{__cp} -r %{_builddir}/%{build_name}/%{_bindir}/* %{buildroot}/%{_bindir}
%{__cp} -r %{_builddir}/%{build_name}/%{_mandir}/* %{buildroot}/%{_mandir}


### The canonical list of files that the package will include.
##
%files
%defattr(755,root,root)
%dir /%{_bindir}
/%{_bindir}/*
/%{_mandir}/man1/*
%attr(0644,root,root) /%{_mandir}/man1/*
#/%{_mandir}/man3/*


### CHANGELOG
##
%changelog
* Mon Aug 1 2016 - walter.g.davies@gmail.com
 - RELEASE-0.1.0
