%%=============================================================================
%% tdtp.cls
%% Copyright 2002 Frédéric Goualard
%%                Institut de Recherche en Informatique de Nantes
%%
%% This program may be distributed and/or modified under the
%% conditions of the LaTeX Project Public License, either version 1.2
%% of this license or (at your option) any later version.
%% The latest version of this license is in
%%   http://www.latex-project.org/lppl.txt
%% and version 1.2 or later is part of all distributions of LaTeX 
%% version 1999/12/01 or later.
%%
%% This program consists of the files listed in manifest.txt
%%
%% CVSId : $Id$
%% Contributions (see ChangeLog) : 
%% - Gyôm <Guillaume.Raschia@irin.univ-nantes.fr>
%%=============================================================================

\def\tdtp@version{2003/09/15, v. 0.8}
\NeedsTeXFormat{LaTeX2e}[1995/12/01]
\ProvidesClass{tdtp-utf8}[\tdtp@version]

\DeclareOption{12pt}{\PassOptionsToClass{12pt}{article}}
\DeclareOption{TD}{\gdef\Type@Feuille{Feuille de travaux dirig\'es}}
\DeclareOption{EXAMEN}{\gdef\Type@Feuille{Examen}}
\DeclareOption{TP}{\gdef\Type@Feuille{Feuille de travaux pratiques}}
\DeclareOption{CC}{\gdef\Type@Feuille{Contr\^ole continu}}
\DeclareOption{CCTP}{\gdef\Type@Feuille{Contr\^ole continu de travaux pratiques}}
\DeclareOption{AUTRE}{\gdef\Type@Feuille{\@TypeFeuillePerso}} 
\DeclareOption{a4paper}{\setlength\paperheight {297mm}%
  \setlength\paperwidth  {210mm}}
\DeclareOption{avecRappel}{\gdef\rappel@correction{o}}
\DeclareOption{sansRappel}{\gdef\rappel@correction{n}}

\ExecuteOptions{a4paper,10pt,oneside,onecolumn,final,avecRappel,TD}
\ProcessOptions\relax
\LoadClass{article}



\renewcommand{\maketitle}{\par
  \begingroup
    \renewcommand\thefootnote{\@fnsymbol\c@footnote}%
    \def\@makefnmark{\rlap{\@textsuperscript{\normalfont\@thefnmark}}}%
    \long\def\@makefntext##1{\parindent 1em\noindent
            \hb@xt@1.8em{%
                \hss\@textsuperscript{\normalfont\@thefnmark}}##1}%
    \if@twocolumn
      \ifnum \col@number=\@ne
        \@maketitle
      \else
        \twocolumn[\@maketitle]%
      \fi
    \else
      \newpage
      \global\@topnum\z@   % Prevents figures from going at top of page.
      \@maketitle
    \fi
    \thispagestyle{fancy}\@thanks
  \endgroup
  \setcounter{footnote}{0}%
}

\newif\ifcorrige

\def\@maketitle{%
  \lhead{}
  \chead{}
  \rhead{}
  \lfoot{{\tiny\@intitule\ --- Universit\'{e} de Nantes}}
  \cfoot{{\tiny\Type@Feuille \ifnum\value{num@TD}>0 % 
      \ \no{}\number\value{num@TD}\fi\ifx\@foottitle\@empty\else~--- \@foottitle\fi}}
  \ifcorrige\rfoot{{\tiny\thepage/\pageref{last@page@feuilleC}}}
  \else\rfoot{{\tiny\thepage/\pageref{last@page@feuille}}}\fi

  \newpage
  \null
  {\large\@cursus \hfill Universit\'e de Nantes}\par{\parindent 0pt
  {\large\@intitule \hfill \annee@scolaire}}
  \vskip 2em
  \begin{center}%
  \let \footnote \thanks
    {\LARGE\em \Type@Feuille\ \ifnum\value{num@TD}>0 \no{}\number%
      \value{num@TD}\fi\par}
    {\LARGE\sf \@title \par}%
    \bigskip
    \ifcorrige\Affiche@BandeauCorrige\fi\par
    \vskip 1.5em%
    {\large \@date}%
  \end{center}%
  \par
  \vskip 1.5em}

\RequirePackage{times}
\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage{fancyhdr}
\pagestyle{fancy}
\RequirePackage[frenchb]{babel}
\RequirePackage{fancyvrb}
\RequirePackage{color}
\RequirePackage{footnote}
\hoffset=-1.9cm
\voffset=-2.6cm
\textwidth=16cm
\textheight=24cm


\def\@TypeFeuillePerso{\ClassError{TdTpIRIN}{pas de type utilisateur défini}{Utilisez la macro \string\TypeUtilisateur\space pour définir votre type de feuille.}}

\newcommand{\TypeUtilisateur}[1]{\gdef\@TypeFeuillePerso{#1}}

\newcounter{num@TD}
\setcounter{num@TD}{-1}
\def\Numero@Feuille#1{\setcounter{num@TD}{#1}}

\newcommand{\cursus}[1]{\gdef\@cursus{{\parindent 0pt #1}}}
\newcommand{\intitule}[1]{\gdef\@intitule{#1}}

\def\annee@scolaire{\ifnum\number\month<8{\advance\year by -1 \number\year/%
    \advance\year by 1 \number\year}%
  \else%
  {\number\year/\advance\year by 1 \number\year}\fi}

% Environnement exercice.
\newcounter{exercice}
\setcounter{exercice}{0}
\def\theexercice{\ifnum\value{num@TD}>0 \arabic{num@TD}.\fi%
  \arabic{exercice}}
\def\exercicename{Exercice}
\def\correxercicename{Corrigé exercice}
\newsavebox{\tmp@Exo}
\newlength{\page@size}
\newenvironment{Exercice@A}[1][]%
  {\setlength{\page@size}{\hsize}\addtolength{\page@size}{-.6em}\par\bigskip%
    \if\rappel@correction o \begin{savenotes}\bgroup\fi\parindent 0pt
    \refstepcounter{exercice}
    \expandafter\newbox\csname ExSaveBox\alph{exercice}\endcsname
    
    \if\rappel@correction o \gdef\boite@Exo{\csname ExSaveBox\alph{exercice}\endcsname}
    \begin{lrbox}{\tmp@Exo}
    \begin{minipage}{\page@size}\fi
    {\bf%
      \if\@obligatoire o \gdef\@obligatoire{n} \hspace*{-9pt}
      {\large$^\star$}\fi%
      \exercicename\ \theexercice%
      \def\@tempa{#1}
      \ifx\@tempa\@empty\expandafter\gdef\csname nb\alph{exercice}\endcsname{}%
      \else~(#1)\expandafter\gdef\csname nb\alph{exercice}\endcsname{~(#1)}%
      \fi}\par\smallskip}%
    {\if\rappel@correction o \end{minipage}\end{lrbox}%
    \global\setbox\boite@Exo=\vbox{\box\tmp@Exo}%
    \egroup\copy\boite@Exo\end{savenotes}\fi}

\newenvironment{Exercice@B}%
  {\par\bigskip\begin{savenotes}\bgroup\parindent 0pt 
    \refstepcounter{exercice}
    {\bf\correxercicename\ \theexercice%
    \csname nb\alph{exercice}\endcsname}\par%
   \if\rappel@correction n\else
   \def\boite@Exo{\csname ExSaveBox\alph{exercice}\endcsname}
   \par\smallskip\hspace*{-.6em}\begin{tabular}{|l}
     \vbox{\unvbox\boite@Exo}
   \end{tabular}\par
   \fi
   \medskip\color{red}\begin{sf}}%
  {\end{sf}\egroup\end{savenotes}}

\newenvironment{solution}{\begin{exercice}}{\end{exercice}}
  
\def\Affiche@BandeauCorrige{\textbf{\textcolor{red}%
    {\LARGE ---~CORRECTION~---}}}

\newcommand{\code}[1]{\textcolor{blue}{\texttt{#1}}}

\def\cleardoublepage{\clearpage\thispagestyle{empty}%
  \ifodd\c@page\else
    \hbox{}\newpage\thispagestyle{empty}\if@twocolumn\hbox{}\newpage\fi\fi}

% Environnement VerbProgram : extension de verbatim pour du code.
\newlength{\numprogskip}
\setlength{\numprogskip}{5pt}
\DefineVerbatimEnvironment{VerbProgram}%
  {Verbatim}{numbers=left,numbersep=\numprogskip,%
  samepage=false,formatcom=\footnotesize,commandchars=\\\@\~}
\def\Rouge#1{\textcolor{red}{#1}}

\def\fichier#1{\par\medskip\bgroup\parindent0pt%
  \textcolor{black}{\textbf{\textrm{Code de \texttt{#1} :}}}\par}
\def\verbInput#1{%
  \VerbatimInput[numbers=left,numbersep=\numprogskip,%
  samepage=false,formatcom=\small]{#1}\egroup}

\renewcommand{\footrulewidth}{.4pt}
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\headwidth}{\hsize}

\def\lastpage@feuille@putlabel{\addtocounter{page}{-1}%
   \immediate\write\@auxout{\string
   \newlabel{last@page@feuille}{{}{\thepage}}{}{}{}}%
   \addtocounter{page}{1}}

\def\lastpage@correction@putlabel{\addtocounter{page}{-1}%
   \immediate\write\@auxout{\string
   \newlabel{last@page@feuilleC}{{}{\thepage}}{}{}{}}%
   \addtocounter{page}{1}}

\newenvironment{feuille}[1][0]{%
  \global\let\exercice\Exercice@A
  \global\let\endexercice\endExercice@A
  \Numero@Feuille{#1}\global\corrigefalse\maketitle}{\clearpage\lastpage@feuille@putlabel}
\newenvironment{correction}{%
  \global\let\exercice\Exercice@B
  \global\let\endexercice\endExercice@B
  \setcounter{exercice}{0}%
  \setcounter{figure}{0}
  \setcounter{table}{0}
  \cleardoublepage
  \global\corrigetrue\setcounter{page}{1}\maketitle}{}

\def\@obligatoire{n}
\newcommand{\obligatoire}{\gdef\@obligatoire{o}}

\let\@foottitle\@empty
\def\title#1{\gdef\@title{#1}\ifx\@foottitle\@empty\gdef\@foottitle{#1}\fi}
\def\foottitle#1{\gdef\@foottitle{#1}}

%\AtEndDocument{\clearpage\label{last@page@feuilleC}}
\AtEndDocument{%
%   \message{AED: lastpage setting LastPage}%
   \clearpage\lastpage@correction@putlabel}%



%% Environnement Program
\newcounter{Program}
\newcounter{TableBAK}
\setcounter{Program}{0}
\newcommand{\numerotageProgram}{\small\red\oldstylenums{\arabic{ProgNumLigne}}}
\newenvironment{programme}{%
  \setcounter{TableBAK}{\value{table}}
  \setcounter{table}{\value{Program}}
  \def\tablename{\textsc{Prog.}}
  \begin{table}[htbp] 
    }{%
  \end{table}
  \setcounter{Program}{\value{table}}
  \setcounter{table}{\value{TableBAK}}}

\endinput

%%% Local Variables: 
%%% mode: latex
%%% TeX-master: t
%%% End: 