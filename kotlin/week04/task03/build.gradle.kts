plugins {
    kotlin("jvm")
    application
}

application {
    mainClassName = "week04.task03.LazyDelegateKt"
}

dependencies {
    compile(kotlin("stdlib"))
    testCompile("junit:junit:4.12")
}
