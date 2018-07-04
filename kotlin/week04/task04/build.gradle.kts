plugins {
    kotlin("jvm")
    application
}

application {
    mainClassName = "week04.task04.DelegatesKt"
}

dependencies {
    compile(kotlin("stdlib"))
    testCompile("junit:junit:4.12")
}
