July2000
---
**July2000** is an open source re-implementation of Dune 2000 aiming to be as
close as possible to the original game.

Building
---
### Windows
Prerequisites: Visual C++ Build Tools.
```bat
$ mkdir build
$ cd build
$ cmake -A win32 ..
$ cmake --build .
```

### Linux for Windows
Prerequisites: MinGW-w64, CMake.
```sh
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

Running
---
To run **July2000**, simply copy `july2000.dll` and `MSS32.DLL` into your game folder
and start the game as usual.

Contributing
---
If you are willing to contribute to this project, please make sure to have
documented your code properly before creating a pull request. Take a look
at [Doxygen](https://doxygen.nl) for more information.

Keep your code consistent with the overall project style and don't leave out
compiler warnings.

Check out the roadmap for the current project progress.

<details>
<summary>Rough Roadmap</summary>
<br>

The numbers after each filename represent virtual address ranges indicating
the location of the compiled-in object modules inside of the original game
executable. Anyone willing to contribute is welcome to help with any of the
below-mentioned files.

```
WW - Westwood Studios library
(+) - done

july2000/moviecode/ahandle.cpp          00401000 - 00401c00 (WW AUDIO.H)
july2000/moviecode/ddstuff.cpp          00401c40 - 00402df0, 00470190 (00401c40 Buffer_Frame_To_Page WW KEYBUFF.CPP, WW BUFFER.CPP WW DDRAW.CPP, WW GBUFFER.CPP)
july2000/moviecode/mono.cpp             004030d0 - 00403430 (WW)
july2000/moviecode/movies.cpp           00403450 - 00403cc0 (00403cc0 Linear_Scale_To_Linear WW DRAWMISC.CPP)
july2000/moviecode/soscodec.asm         00404860 - 004048c0 (WW SOSCOMP.H, ADPCM.CPP)
july2000/moviecode/unvqtblc.cpp         00404cd8 - 00404b30
july2000/moviecode/vqa.cpp              00405fa0 - 00407400 (WW)
july2000/moviecode/wnd_file.cpp         00407480 - 004078c0 (WW)

july2000/netcode/ipbuf.cpp              00402e80 - 004030b0
july2000/netcode/sockbuf.cpp            00403b50 - 00403c60
july2000/netcode/wsproto.cpp            004078d0 - 00407d70 (WW WSPROTO.CPP)
july2000/netcode/wspudp.cpp             00407d90 - 00408110 (WW WSPUDP.CPP)
july2000/netcode/field.cpp              004082b0 - 004084d0 (WW FIELD.CPP)
july2000/netcode/packet.cpp             00408540 - 00408580 (WW PACKET.CPP)
july2000/netcode/wol.cpp                00408670 - 0041af30

july2000/code/ai.cpp                    0041af50 - 00423850
july2000/code/display.cpp               00423990 - 0042b670
(+) july2000/code/file.cpp              0042b730 - 0042ba50
july2000/code/globe.cpp                 0042bc60 - 0042d110
july2000/code/graphlib.cpp              0042d140 - 0042e450
july2000/code/image.cpp                 0042e660 - 004353b0
july2000/code/interface.cpp             004359a0 - 0043d150
july2000/code/credits.cpp               0043d150 - 0043d520
july2000/code/score.cpp                 0043d7e0 - 004412c0
july2000/code/loadsave.cpp              004414d0 - 004422c0
july2000/code/main.cpp                  00442310 - 0044c460
july2000/code/map.cpp                   0044c480 - 0044f440
(+) july2000/code/memory.cpp            0044f490 - 0044f6f0
july2000/code/mission.cpp               0044f770 - 00455500
july2000/code/model.cpp                 00455510 - 00458e90
july2000/code/order.cpp                 00459450 - 0045d390
(+) july2000/code/particle.cpp          0045d440 - 0045d730
july2000/code/route.cpp                 0045d990 - 0045fe20
july2000/code/setup.cpp                 0045fe70 - 0046b690
july2000/code/side.cpp                  0046bd40 - 0046eb00, 004a45d0 - 004a4740
july2000/code/sound.cpp                 0046eb60 - 00470170
(+) july2000/code/cd.cpp                004a61d0 - 004a63d5
july2000/code/uimanager.cpp             004706c0 - 004825b0
july2000/code/uiobject.cpp              00482780 - 00484f10
july2000/code/uibutton.cpp              00485000 - 00485610
july2000/code/uitogglebutton.cpp        00485940 - 00485ce0
july2000/code/uigroupbox.cpp            004860e0 - 004863a0
july2000/code/uilistbox.cpp             00486440 - 004885f0
july2000/code/uicheckbox.cpp            0048ab10 - 0048adc0
july2000/code/uimultibox.cpp            0048af30 - 0048b0e0
july2000/code/uieditbox.cpp             0048b190 - 0048b560
july2000/code/uitextbox.cpp             0048b9c0 - 0048bb10
july2000/code/uivaluebar.cpp            0048c030 - 0048cbf0
july2000/code/uianim.cpp                0048cec0 - 0048d650
july2000/code/uimovie.cpp               0048d730 - 0048d8f0
july2000/code/uidata.cpp                0048d980 - 00493350
july2000/code/unit.cpp                  00493590 - 0049fb40, 004a47f0 - 004a60e0
july2000/code/wignet.cpp                0049fb90 - 004a3080
july2000/code/winmain.cpp               004a3120 - 004a4560

july2000/vqa32/unvqbuff.asm             004a6590 - 004a6aba (WW)
july2000/vqa32/config.cpp               004a6ba0            (WW)
july2000/vqa32/vqaplay.cpp              004a6bc0 - 004a7310 (WW)
july2000/vqa32/task.cpp                 004a76f0 - 004a7eb0 (WW)
july2000/vqa32/loader.cpp               004a7ee0 - 004ab010 (WW)
july2000/vqa32/drawer.cpp               004ab0b0 - 004abcc0 (WW)
july2000/vqa32/audio.cpp                004abcd0 - 004ac130 (WW)
july2000/vqa32/memory.cpp               004ac200 - 004ad060 (WW)
july2000/vqa32/stream.cpp               004ad060 - 004ad310 (WW)
july2000/vqa32/timer.cpp                004ad3e0 - 004ad420 (WW)
july2000/vqa32/unvqbuff.cpp             004ad450 - 004af2c0 (WW)                  
july2000/vqa32/soscomp.asm              004af650 - 004af671 (WW SOSCOMP.H, ADPCM.CPP)
july2000/vqa32/lcwuncmp.asm             004b0220 - 004b02eb (WW LCWUNCMP.CPP)
july2000/vqa32/audunzap.asm             004b0480            (WW)
```

Because the development of this game was outsourced to Intelligent Games,
Westwood Studios had to provide them with their own C++ support library
to use the Westwood file formats (AUD, VQA) and utilise the online-play
API. Most of its source code was released alongside
Command & Conquer: Remastered Collection, which you may find [here](https://github.com/electronicarts/CnC_Remastered_Collection).

</details>

Licence
---
The source code provided in this repository is licensed under the [GNU General Public
License Version 3](https://www.gnu.org/licenses/old-licenses/gpl-3.0.html).
This project has no affiliation with Westwood Studios, Intelligent Games or
Electronic Arts. It is a purely voluntary effort with no endorsement from
any of the aforementioned parties.
