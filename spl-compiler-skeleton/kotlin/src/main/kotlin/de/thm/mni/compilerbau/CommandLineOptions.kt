package de.thm.mni.compilerbau

import java.io.*
import kotlin.system.exitProcess

class CommandLineOptions {

    enum class PhaseOption {
        TOKENS, PARSE, ABSYN, TABLES, SEMANT, VARS
    }

    @JvmField
    var phaseOption: PhaseOption? = null

    @JvmField
    var ershovOptimization = false

    @JvmField
    var doWhileEnabled = false

    @JvmField
    var firstClassBoolean = false

    @JvmField
    var nestedScopesEnabled = false

    @JvmField
    var leafProcedureOptimization = false

    @JvmField
    var recordsEnabled = false

    @JvmField
    var valueSemanticsEnabled = false

    @JvmField
    var compoundLiteralsEnabled = false

    // get() = field
    var inFilename = ""
    var outFilename = ""

    @JvmName("setPhaseOption1")
    fun setPhaseOption(phaseOption: PhaseOption?) {
        if (this.phaseOption != null) usageError("More than one phase option specified.")
        this.phaseOption = phaseOption
    }

    // Unclosable stream to avoid closing stdout when no output file is given.
    // Source: https://stackoverflow.com/a/23791138
    @get:Throws(IOException::class)
    val outputWriter: PrintWriter
        get() {
            // Unclosable stream to avoid closing stdout when no output file is given.
            // Source: https://stackoverflow.com/a/23791138
            class UnclosableOutputStream(out: OutputStream?) : FilterOutputStream(out) {
                @Throws(IOException::class)
                override fun close() {
                    out.flush()
                }
            }
            return if (outFilename.isEmpty()) PrintWriter(UnclosableOutputStream(System.out)) else PrintWriter(
                FileWriter(
                    outFilename
                )
            )
        }

    companion object {
        private fun usageError(format: String, vararg args: Any) {
            System.err.printf("Usage error: $format", *args)
            System.err.println()
            showUsage(System.err)
            System.exit(1)
        }

        private fun showUsage(out: PrintStream) {
            out.println("Usage: 'java -jar spl.jar' [OPTION] INPUT_FILE [OUTPUT_FILE]")
            out.println()
            out.println("Executes all compiler phases up to (and including) the specified one.")
            out.println("If no flag is specified, all phases are run and code is written to the output file.")
            out.println("Options:")
            out.println("  --tokens            Phase 1: Scans for tokens and prints them.")
            out.println("  --parse             Phase 2: Parses the stream of tokens to check for syntax errors.")
            out.println("  --absyn             Phase 3: Creates an abstract syntax tree from the input tokens and prints it.")
            out.println("  --tables            Phase 4a: Builds a symbol table and prints its entries.")
            out.println("  --semant            Phase 4b: Performs the semantic analysis.")
            out.println("  --vars              Phase 5: Allocates memory space for variables and prints the amount of allocated memory.")
            out.println("  --doWhile           Enable the do-while statement.")
            out.println("  --bool              Enable boolean variables and logical operators & and |.")
            out.println("  --scopes            Enable the declaration of variables inside of compound statements.")
            out.println("  --ershov            Enable register optimization using the ershov number.")
            out.println("  --leafProc          Enables the optimization of leaf procedures.")
            out.println("  --records           Enable support for records.")
            out.println("  --valueSemantics    Enable value semantics.")
            out.println("  --compoundLiterals  Enable array and record literals.")
            out.println("  --help              Show this help.")
        }

        fun parse(args: Array<String>): CommandLineOptions {
            val options = CommandLineOptions()
            for (name in args) {
                when (name) {
                    "--tokens" -> options.setPhaseOption(PhaseOption.TOKENS)
                    "--parse" -> options.setPhaseOption(PhaseOption.PARSE)
                    "--absyn" -> options.setPhaseOption(PhaseOption.ABSYN)
                    "--tables" -> options.setPhaseOption(PhaseOption.TABLES)
                    "--semant" -> options.setPhaseOption(PhaseOption.SEMANT)
                    "--vars" -> options.setPhaseOption(PhaseOption.VARS)
                    "--ershov" -> options.ershovOptimization = true
                    "--doWhile" -> options.doWhileEnabled = true
                    "--bool" -> options.firstClassBoolean = true
                    "--scopes" -> options.nestedScopesEnabled = true
                    "--leafProc" -> options.leafProcedureOptimization = true
                    "--records" -> options.recordsEnabled = true
                    "--valueSemantics" -> options.valueSemanticsEnabled = true
                    "--compoundLiterals" -> options.compoundLiteralsEnabled = true
                    "--help" -> {
                        showUsage(System.out)
                        exitProcess(0)
                    }

                    else -> if (!name.startsWith("--")) {
                        if (options.inFilename.isEmpty()) options.inFilename = name
                        else if (options.outFilename.isEmpty()) options.outFilename = name
                        else usageError("Too many positional arguments!")
                    } else {
                        usageError("Unknown option '%s'!", name)
                    }
                }
            }
            if (options.inFilename.isEmpty()) usageError("No input file!")
            return options
        }
    }
}
