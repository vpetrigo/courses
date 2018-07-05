plugins {
    kotlin("jvm")
    application
}

application {
    mainClassName = "week05.task01.IntExtensionKt"
}

dependencies {
    compile(kotlin("stdlib"))
    testCompile("junit:junit:4.12")
}
