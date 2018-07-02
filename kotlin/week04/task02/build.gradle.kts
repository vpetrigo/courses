plugins {
    kotlin("jvm")
    application
}

application {
    mainClassName = "week04.task02.LazyPropertyKt"
}

dependencies {
    compile(kotlin("stdlib"))
    testCompile("junit:junit:4.12")
}
