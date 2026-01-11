#import "@preview/ezexam:0.2.7": *

#set document(
    title: "山东大学计算机科学与技术学院24数据、智能班数据结构期末",
    author: "Arshtyi",
    date: datetime.today(),
)

#show: setup.with(
    mode: EXAM,
)

#show link: it => {
    set text(fill: blue)
    underline(it)
}

#title[
    山东大学计算机科学与技术学院

    24数据、智能班数据结构与算法期末试题
]

#notice(
    [出于方便使用#link("https://github.com/gbchu/ezexam", "gbcnu/ezexam:0.2.7").],
    [源码:#link("https://github.com/Arshtyi/SDU-Data-Struct").],
    [实际为机试(SDUCSOnline).],
)
