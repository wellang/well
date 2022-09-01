# Compiling Wellang on Windows

### Requirements:

-	(Optional): https://chocolatey.org/
-	git:	https://git-scm.com/download/win
-	nasm:	https://www.nasm.us/pub/nasm/releasebuilds/?C=M;O=D
-	mingw:	https://www.mingw-w64.org/

After installing the requirements for wellang on windows do the following:

1.  Open cmd/and or windows powershell
2.  go to desired directory. ex: ``cd /path/to/Downloads``
3.  download wellang: ``git clone https://wellang/well.git``
4.  ``cd well``
5.  install wellang: ``make base install``

## Adding wellang to Path variables

1.  Go to ``Edit the system environment variables`` through the control pannel, or go to ``system properties``
2.  click on ``environment variables``
3.  find ``path`` in the environment variables
4.  click ``edit``
5.  click ``new`` and enter the wesm compiler directory
6.  press ``enter`` and click ``ok``
