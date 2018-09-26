plugins {
    application
}

application {
    mainClassName = "section01.task123.MatrixMax"
}

java {
    sourceCompatibility = JavaVersion.VERSION_1_8
    targetCompatibility = JavaVersion.VERSION_1_8
}

var compileSystem = org.gradle.internal.os.OperatingSystem.current()!!
var platform: String = ""

when {
    compileSystem.isWindows -> platform = "win"
    compileSystem.isLinux -> platform = "linux"
    compileSystem.isMacOsX -> platform = "mac"
}

dependencies {
    implementation("org.openjfx:javafx-base:11:$platform")
}

tasks.withType<JavaExec> {
    standardInput = System.`in`
}
