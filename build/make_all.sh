#!/bin/bash

### @file make_all.sh
## This script takes the source trees and builds an RPM
##
PATH=/bin:/usr/bin:/usr/sbin;

declare top="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )";
declare tld="${top}/..";
declare PROJECT="fsls";
declare SPEC="${top}/${PROJECT}.spec";
declare VFILE="${tld}/version";
declare SED="$(which sed || exit 1)";
declare GIT="$(which git || exit 1)";
declare project_name release_string version_string;

declare -i bld build;
declare -i ret_val=0 debug=0 force=0 noupd=0 bsrpm=0;

if [[ $@ =~ debug ]]; then debug=1; fi;
if [[ $@ =~ force ]]; then force=1; fi;
if [[ $@ =~ noupd ]]; then noupd=1; fi;
if [[ $@ =~ bsrpm ]]; then bsrpm=1; fi;

run () {
    local -a cmdline=( $@ );
    local cmd="${cmdline[0]}";

    ${cmdline[*]};
    ret_val=$?;

    if (( ret_val != 0 )); then
	echo "error: ${cmd} failed";
	exit ${ret_val};
    fi;
}

prepare_build () {
    local spec_file build_dir bin_dir man_dir project; 

    spec_file="rpmbuild/SPECS/${project_name}.spec";
    build_dir="${tld}/${project_name}";
    bin_dir="${build_dir}/usr/local/bin";
    man_dir="${build_dir}/usr/local/man";
    
    run mkdir -p ${bin_dir} ${man_dir};
#    run cp -v ${tld}/README.md ${build_dir};
    run cp -rv ${tld}/doc/man/* ${man_dir};

    for project in ${tld}/*; do 
	project=${project##*/};

	case ${project} in 
	    Makefile|README*|build|doc|lib|version|${project_name}) echo "skipping ${project}" ;;
	    *) run cp -pv ${tld}/${project}/${project} ${bin_dir} ;;
	esac;
    done;

    run tar -czvf ${project_name}.tar.gz ${build_dir};
    run rm -rf ${top}/rpmbuild;
    run mkdir -p rpmbuild/{BUILD,RPMS,SOURCES,SPECS,SRPMS};
    run mv ${project_name}.tar.gz rpmbuild/SOURCES/;
    run cp ${SPEC} ${spec_file};
}

make_build () {
    local build_type;
    local debug_string;
    
    if (( bsrpm == 0 )); then
	build_type='-bb';
    else
	build_type='-ba';
    fi;

    if (( debug != 0 )); then
	debug_string='--rpmfcdebug -vv';
    fi;

    rpmbuild ${build_type} ${debug_string} \
	--define "_topdir ${top}/rpmbuild" \
	--define "_version ${version_string}" \
	--define "_buildnum ${build}" \
	rpmbuild/SPECS/${project_name}.spec;
}

cleanup () {
    run cp rpmbuild/RPMS/x86_64/${project_name}*.rpm ${top};

    if (( bsrpm == 1 )); then
	run cp rpmbuild/SRPMS/${project_name}.src.rpm ${top};
    fi;

    if (( debug == 0 )); then
	run rm -rf ${tld}/${project_name} ${top}/rpmbuild;
    fi;
}

if (( debug == 1 )); then set -x; fi;

release_string=$(${GIT} symbolic-ref HEAD);

if [[ ${release_string} =~ RELEASE ]]; then
    version_string=${release_string##*-};
elif (( force == 1 )); then
    version_string=$(cut -d- -f1 < ${tld}/version);
else
    echo "ERROR: must create RPM from a Git RELEASE branch (or force creation)";
    exit 1;
fi;

bld=$(cut -d- -f2 < ${VFILE});

if (( noupd == 0 )); then
    build=$(( ++bld ));
else
    build=${bld};
fi;

printf "\nCreating RPM for Release %s, Build number %d\n\n" ${version_string} ${build};
sleep 3;

project_name="${PROJECT}-${version_string}";
    
cd ${top};
prepare_build;
make_build;
cleanup;

if (( debug == 1 )); then set +x; fi;

printf "%s-%d\n" ${version_string} ${build} > ${VFILE};
printf "\n\n\tRPM files for %s created under ${top}\n" ${PROJECT};
printf "\tVersion file updated to %s-%d\n\n" ${version_string} ${build};
