<div lang="fr">

# Guide de contribution pour le développement de XIOS



</div>

<div lang="en">
   
# Contributing Guide for XIOS development

## Git Code Maintenance

* All development activity shall be pushed to a personal fork of the project.
* Development shall only be included into this https://gitlab.in2p3.fr/ipsl/projets/xios project via `merge request`.

The https://gitlab.in2p3.fr/ipsl/projets/xios project is referred to as `upstream` in this guide.

### Simple Git Workflow

It is assumed that you have a local git repository where `origin` is your https://gitlab.in2p3.fr fork
and `upstream` is https://gitlab.in2p3.fr/ipsl/projets/xios.

This work flow is for proposing changes to `main`, currently `XIOS3`.

1. `git fetch origin`
1. `git checkout -b {new-branch-name} upstream/main`
1. < development activity >
1. < local testing >
1. `git commit`
1. `git push origin {new-branch-name}`
1. raise new `merge request` on `gitlab.in2p3.fr`
  * This should trigger the CI testing for the `merge request`

Further Git work flows are possible for making changes to release branches and older versions of XIOS
and for managing more complicated changes.

### Feature Branches

For large scale changes that require coherent adoption, then a developer may choose to create a
`Feature Branch` within their fork.

This branch can be contributed to by one or numerous developers.
Parts of the full feature may be reviewed and adopted into the feature branch by
`Merge Request`s within the lead developers fork.

Once Ready then the `Feature Branch` may be proposed to the `upstream` code base, with links to
all of the intermediate `Merge Request` reviews.

This work flow can significantly help to manage larger and more invasive changes to the code base.
For many development activities then it is not required and the simple work flow is fine.

## Issue tracking

### Merge Request

Any development activity targeting the `upstream` shall be associated with a `Merge Request` to `upstream`.

## Review & Merge

* Code proposals shall be reviewed, by one of more code reviewers, with comments added to the `Merge Request` and updates to the branch, until the reviewer(s) are content.
* Reviewers shall use the `Review` section to request changes or indicate that they are content.
* Merge of merge request branch content onto an upstream branch  shall be undertaken by one the the XIOS core developers.
* XIOS core developers may deem some changes to be particularly minor and implement the review and merge process directly themselves, via a `Merge Request`.

### Issue Tracking

https://gitlab.in2p3.fr/ipsl/projets/xios is an open issue tracker for XIOS development.

Merge Requests may link to Issues, and may explicitly close Issues or simply contribute to them.

It is not essential to have an Issue and a Merge Request for small changes, but for larger changes or Issues without solution, then an Issue is useful to manage awareness and work.  this is particularly the case when designing new features.

### Design Principles & design Review

XIOS aims to provide applicable Input Output data flow services for simulations, the first implementation is IO servers.
XIOS tries to avoid embedding model specific code within it's implementation. Features should be generally useful and implemented such
that models provide their own customisations through model configuration of XIOS.

New features should be proposed to XIOS using a design review ticket. This enables the general target and
the implementation targets to be explored and the design principles discussed prior to the proposal
of detailed code changes.

A design review ticket shall include:
* a statement of desired outcome;
* a description of the context and value being targeted;
* a proposal on how this could be implemented within the XIOS code base;
* a proposal on how the user interface could be implemented:
    * to meet the specific needs of the propser and to be extensible and useful generally;
* how the new feature can be tested;
* an initial assessment of risks to existing areas of the code base.

Small features and bug fixes may bypass this design review stage, if agreed by the XIOS development team.
It is fine to raise a `Merge Request` if you feel that the work is small.  If XIOS developers would
appreciate a design review Issue for the work, then we will tell you.

## Major Version Targeting

* XIOS3 is the current major development version.

* XIOS2 is a backwards incompatible stable version.
* XIOS2 is still in broad use in some simulations, but is not undergoing further development.

The source trees for these major versions are divergent, so management is needed for development targeting.

### Major Version Development Rules

1. Bug fixes may apply to:
    * XIOS3 `main` only:
        * this is the default approach;
    * `XIOS2` branch & XIOS3 `main`:
        * if the bug is demonstrated to be causing problems for users of XIOS2;
        * in this case, create two branches linked to one ticket, to manage the bug fix.
    * `XIOS2` branch only, if this has no bearing on XIOS3 `main`:
        * if the bug is demonstrated to be causing problems for users of XIOS2 and shown to be not evident in XIOS3.
    * a specific release branch may also be targeted by a ticket:
        * only the latest release should be targeted for a bug fix:
            * unless a specific case is made and agreed on a ticket for why one further older release branch should be included as well;
        * a release branch bug fix shall always be considered for proposal to `main` XIOS3:
            * though testing may show that this is not required (e.g. already resolved on `main`).
1. New Features
    * New features may be proposed to XIOS3 only:
        * this is the default position for development effort;
        * it is recognised that most new features shall not be available in XIOS2.
    * New features may be proposed to XIOS3, with a back port to XIOS2:
        * this is an unusual case, the expectation is that new features are not added to XIOS2;
        * if the feature is reviewed and assessed as appropriate for linked development, it may target XIOS2 and XIOS3, by exception;
        * two linked branches targeting XIOS2 & XIOS3 are provided, linked to one ticket. 
    * New features may not be applied to XIOS2 only:
        * XIOS2 is not being developed independent of XIOS3.

## Interface Code Generation

Fortran, C++ & Python interface source code is generated from configurations by tools within the XIOS code base.

* It is the responsibility of a developer to test that the Fortran code generation is functional and effective
* It is the responsibility of a developer to ensure that the code generation tool has ben run on their Merge Request and the resulting generated code checked into the branch.
* The repository CI testing will verify that the generated code is identical to the code submitted by the developer.

In order to generate interface code, it is necessary to first compile the interface tooling. 
This is enabled by editing the `bld.cfg` [configuration file](bld.cfg#L53) in a local copy, and uncommenting the line:
```
bld::target generate_interfaces.exe
```

Then, compiling XIOS using `./make_xios` will also create the `generate_interfaces.exe` executable within the `bin` directory.

(Please remember to revert your change to `bld.cfg`, don't commit this to your branch for any Merge Request)

To run the interface generation code and locate the outputs in the correct places within the source, then:
```
cd src
./../bin/generate_interfaces.exe
mv interface/*_attr.cpp interface/c_attr/
mv interface/*_attr.F90 interface/fortran_attr/
mv interface/*_attr.py interface/python/xios/
```

You can then use 
```
git diff
```
to explore and verify that any changes are as you expect.
Changes need to be commited to your development branch as your changes for any Merge Request proposal.

This process is repeated within the Continuous Integration testing pipeline, which should verify that the interface code is consistent with the source for any Merge Request.
([.gitlab-ci.yml#L18](.gitlab-ci.yml#L18) [.gitlab-ci.yml#L37](.gitlab-ci.yml#L37))

</div>
