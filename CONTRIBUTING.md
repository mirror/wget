# Wget Contribution Guidelines

1.  [Guidelines For Patch
    Submissions](#Guidelines_For_Patch_Submissions)
    1.  [What is a patch ?](#What_is_a_patch.3F)
    2.  [Where to send the patches](#Where_to_send_the_patches)
    3.  [Standards and coding style](#Standards_and_coding_style)


Guidelines For Patch Submissions {#Guidelines_For_Patch_Submissions}
================================

What is a patch ? {#What_is_a_patch.3F}
-----------------

A patch file, also known as a \"diff\", is a textual representation of
changes to source code. Patches are readable enough
to be reviewed by []{#line-9 .anchor}humans and at the same time regular
enough to be processed by programs. The `patch`
utility is used to change the source code in the
manner that the patch describes, this being called \"applying\" the
patch. Patches work even on files that have been
modified independently of the modifications in the
patch, as long as those other changes do not
conflict with the patch.

Because of these properties, patches are the preferred means of
distributing the changes to a free software project.
If you have made a change to Wget and would like to
contribute it, you will need to create a patch and
send it to the developers; please read on.

Where to send the patches {#Where_to_send_the_patches}
-------------------------

Patches intended to be applied to Wget should be mailed to
bug-wget@gnu.org. Each patch will be reviewed by the
developers, and will be acked and added to the
distribution, or rejected with an explanation.
Unfortunately, the developers are often busy with
their day jobs, so the review process can take a while.

*Every* patch should be accompanied by an explanation of what the patch
changes, and why the change is desirable or
necessary. The explanation need not be long, but
please don\'t just send a patch without any
accompanying text.

Please send your patches as email attachments. It is important that the
patch survives the travel unchanged so that we can feed it to
the `patch` utility or `git am/apply` after or while reviewing it.


Standards and coding style {#Standards_and_coding_style}
--------------------------

Wget abides by the GNU coding standards, available at:

-   https://www.gnu.org/prep/standards.html

But maybe even better is to stay with the surrounding coding style.

When working with git: The commit messages needs a certain GNU style
format. Please check `git log` for examples. The maintainers might
correct small issues here before pushing / applying without asking.
